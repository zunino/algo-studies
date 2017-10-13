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
            let e1 = sorted[i];
            let e2 = sorted[i + 1];
            if (e1 > e2) {
                let tmp = e1;
                sorted[i] = sorted[i + 1];
                sorted[i + 1] = tmp;
                swapped = true;
            }
        }
    } while (swapped);
    return sorted;
}

const collection = [5, 1, 4, 7, 2, 12, 6, 8];
console.log(bubbleSort(collection));

