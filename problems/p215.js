let start = +new Date();

let cache = {};
function W(prev, acc, max_r, r, c) {
    let tup = [prev, acc, r, c];

    if (tup in cache) {
        return cache[tup];
    }
    else if (r == 0 && c == 1) {
        return 1;
    }


    let tot = 0;
    if (r == 0 && c > 1) {
        return W(acc, [], max_r, max_r, c - 1);
    }
    else {
        for (let i = 0; i < 2; i++) {
            let d = [2, 3][i];
            let n = r - d;
            if (n == 0 || (n > 0 && !prev.includes(n))) {
                tot += W(prev, acc.concat(n), max_r, n, c);
            }
        }
    }

    cache[tup] = tot;
    return tot
}

let a = W([], [], 32, 32, 10);
console.log(`Solution: ${a}`);

let end = +new Date();
console.log(`${(end - start) / 1000.0} seconds to run`)
