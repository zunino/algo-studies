function quicksort(array, start = 0, end = array.length) {
    if (end - start < 2) {
        return array;
    }
    let pivot = array[end - 1];
    let wall = start;
    for (let i = start; i < end - 1; ++i) {
        if (array[i] < pivot) {
            if (i != wall) {
                swap(array, i, wall);
            }
            ++wall;
        }
    }
    if (wall < end - 1) {
        swap(array, end - 1, wall);
    }
    quicksort(array, start, wall);
    quicksort(array, wall + 1, end);
}

function swap(arr, i, j) {
    const temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
};

function spaced(array) {
    return `[${array.join(' ')}]`;
}

function testQuicksort(input, output) {
    if (input.length != output.length) {
        console.error(`Test arguments ${input} and ${output} differ in length.`);
        return;
    }
    const sorted = input.slice();
    quicksort(sorted);
    console.log(`${spaced(input)} => ${spaced(sorted)}`);
}

testQuicksort([7], [7]);
testQuicksort([7, 4], [4, 7]);
testQuicksort([7, 4, 9], [4, 7, 9]);
testQuicksort([4, 3, 19, 6, 2], [2, 3, 4, 6, 19]);
testQuicksort([4, 12, 6, 1, 5], [1, 4, 5, 6, 12]);
testQuicksort([5, 8, 2, 6, 9, 1], [1, 2, 5, 6, 8, 9]);
testQuicksort([2, 8, 5, 9, 3, 1, 4, 5], [1, 2, 3, 4, 5, 5, 8, 9]);
testQuicksort([4, 10, 1, 6, 3, 8, 2, 4, 0, 5], [0, 1, 2, 3, 4, 4, 5, 6, 8, 10]);
