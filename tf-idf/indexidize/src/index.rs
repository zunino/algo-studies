use std::io;
use std::{
    collections::HashMap,
    fs::{read_dir, read_to_string},
};

const STOP_WORDS_EN: &[&str; 21] = &[
    "a", "in", "is", "it", "on", "of", "or", "as", "by", "to", "was", "who", "why", "what", "how",
    "and", "but", "for", "the", "that", "this",
];

// const STOP_WORDS_PT: &[&str; 16] = &[
//     "a", "o", "e", "é", "de", "na", "no", "em", "um", "uma", "mas", "por", "pra", "que", "já",
//     "para",
// ];

const PUNCTUATION: &str = ".,;-\"'[](){}|/";

type DocId = usize;
type Term = String;
type Terms = Vec<String>;
type Corpus = HashMap<DocId, Terms>;

type DocumentPaths = Vec<String>;
type TermFrequency = HashMap<DocId, usize>;
type TermFrequencies = HashMap<Term, TermFrequency>;
type TermScore = HashMap<DocId, f32>;
type TermScores = HashMap<Term, TermScore>;
type SearchResult = Vec<(String, f32)>;

fn tokenize(content: &str) -> Terms {
    let lower_content = content.to_lowercase();
    let chars = lower_content.chars();
    let mut clean_content = String::with_capacity(lower_content.len());
    for c in chars {
        if PUNCTUATION.chars().any(|p| c == p) {
            clean_content.push(' ');
            continue;
        }
        clean_content.push(c);
    }
    clean_content
        .trim()
        .split_whitespace()
        .filter(|t| !STOP_WORDS_EN.iter().any(|w| t == w))
        // .filter(|t| !STOP_WORDS_PT.iter().any(|w| t == w))
        .map(|t| String::from(t))
        .collect()
}

fn read_corpus(corpus_path: &str) -> io::Result<(DocumentPaths, Corpus)> {
    let mut document_paths = DocumentPaths::new();
    let mut corpus = Corpus::new();
    let dir_iter = read_dir(corpus_path)?;
    for dir_entry in dir_iter {
        let file_path = String::from(dir_entry?.path().to_str().unwrap());
        document_paths.push(file_path.clone());
        let doc_id = document_paths.len() - 1;
        let content = read_to_string(&file_path)?;
        corpus.insert(doc_id, tokenize(&content));
    }
    Ok((document_paths, corpus))
}

fn calculate_term_frequencies(corpus: &Corpus) -> TermFrequencies {
    let mut term_frequencies = TermFrequencies::new();
    for (doc_id, terms) in corpus.iter() {
        for term in terms {
            let term_entry = term_frequencies.entry(term.clone()).or_default();
            let doc_entry = term_entry.entry(doc_id.clone()).or_insert(0);
            *doc_entry += 1;
        }
    }
    term_frequencies
}

fn calculate_term_scores(
    docs: &DocumentPaths,
    corpus: &Corpus,
    frequencies: &TermFrequencies,
) -> TermScores {
    let mut term_scores = TermScores::new();
    for (term, doc_frequencies) in frequencies {
        let mut term_score = TermScore::new();
        for (doc_id, doc_freq) in doc_frequencies {
            let tf = calculate_tf(corpus, *doc_id, *doc_freq);
            let idf = calculate_idf(docs, frequencies, term);
            let tf_idf_score = tf * idf;
            term_score.insert(*doc_id, tf_idf_score);
        }
        term_scores.insert(term.clone(), term_score);
    }
    term_scores
}

fn calculate_tf(corpus: &Corpus, doc_id: DocId, doc_freq: usize) -> f32 {
    let doc_term_count = corpus.get(&doc_id).unwrap().len();
    doc_freq as f32 / doc_term_count as f32
}

fn calculate_idf(docs: &DocumentPaths, frequencies: &TermFrequencies, term: &Term) -> f32 {
    let all_docs = docs.len();
    let doc_freq = frequencies.get(term);
    let docs_with_term = match doc_freq {
        Some(doc_freqs) => doc_freqs.len(),
        None => 0,
    };
    let idf_quotient = all_docs as f32 / 1.0 + docs_with_term as f32;
    idf_quotient.log10()
}

#[derive(Debug)]
pub struct TfIdfModel {
    docs: DocumentPaths,
    scores: TermScores,
}

impl TfIdfModel {
    pub fn build(corpus_path: &str) -> io::Result<Self> {
        println!("Building TF-IDF model from '{corpus_path}'");
        let (docs, corpus) = read_corpus(corpus_path)?;
        let frequencies = calculate_term_frequencies(&corpus);
        let scores = calculate_term_scores(&docs, &corpus, &frequencies);

        Ok(Self { docs, scores })
    }

    pub fn search(&self, query: &str) -> SearchResult {
        let search_terms = tokenize(query);
        let mut doc_score_map = HashMap::<String, f32>::new();
        for term in search_terms {
            let doc_scores = self.scores.get(&term);
            if let None = doc_scores {
                continue;
            }
            for (doc_id, score) in doc_scores.unwrap() {
                let doc_path = self.docs[*doc_id].clone();
                doc_score_map
                    .entry(doc_path)
                    .and_modify(|s| *s += score)
                    .or_insert(*score);
            }
        }
        let mut search_result: SearchResult = doc_score_map
            .iter()
            .map(|(doc, score)| (doc.clone(), *score))
            .collect();
        search_result.sort_by(|lhs, rhs| rhs.1.partial_cmp(&lhs.1).unwrap());
        search_result
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_tokenize_should_make_lowercase_tokens_ignoring_stop_words_and_punctuation() {
        let tokens = tokenize("Things of importance that aren't in the (aforementioned) article.");
        assert_eq!(5, tokens.len());
        assert_eq!(
            vec![
                "things",
                "importance",
                "aren't",
                "aforementioned",
                "article"
            ],
            tokens
        );
    }
}
