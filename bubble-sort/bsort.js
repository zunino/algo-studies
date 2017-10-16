function bubbleSort(coll) {
    const sorted = Array.from(coll);
    const len = sorted.length;
    if (len < 2) {
        return sorted;
    }
    let swapped;
    do {
        swapped = false;
        for (let i = 0; i <= (len - 2); ++i) {
            if (sorted[i] > sorted[i + 1]) {
                [sorted[i], sorted[i + 1]] = [sorted[i + 1], sorted[i]];
                swapped = true;
            }
        }
    } while (swapped);
    return sorted;
}

const collection = [5, 1, 4, 7, 2, 12, 6, 8];
console.log(bubbleSort(collection));

