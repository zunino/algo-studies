function quicksort(array, start = 0, end = array.length) {
    if (end - start < 2) {
        return array;
    }
    let pivot = array[end - 1];
    let wall = start;
    for (let i = start; i < end - 1; ++i) {
        if (array[i] < pivot) {
            if (i != wall) {
                sswap(array, i, wall);
            }
            ++wall;
        }
    }
    if (wall < end - 1) {
        sswap(array, end - 1, wall);
    }
    quicksort(array, start, wall);
    quicksort(array, wall, end);
}

function sswap(arr, i, j) {
    const temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
};

const array1 = [4, 12, 6, 1, 5];

console.log(array1);
quicksort(array1);
console.log(array1);