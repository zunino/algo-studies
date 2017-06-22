const values1 = [1, 2, 3, 4, 5];
const values2 = [2, 7, 1, 9, 10, 8, 6];

function partialSums(values) {
    let psums = [];
    psums.push(values[0]);
    for (let i = 1; i < values.length; ++i) {
        psums.push(psums[i - 1] + values[i]);
    }
    return psums;
}

console.log("Values:", values1);
console.log("Partial sums:", partialSums(values1));
console.log();
console.log("Values:", values2);
console.log("Partial sums:", partialSums(values2));

