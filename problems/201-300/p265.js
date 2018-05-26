var start = +new Date();
var count = 0;

function S(n, r, str) {
    if (str.slice(0, -1).indexOf(str.slice(-n)) !== -1) {
        return 0;
    } else if (r <= 0) {
        var t = str + str.slice(0, n - 1);
        for (var i = 0; i < 2 ** n; i++) {
            if (t.slice(0, i + n - 1).indexOf(t.slice(i, i + n)) !== -1) {
                return 0;
            }
        }
        count += 1;
        return parseInt(str, 2);
    }
    return S(n, r - 1, str + '0') + S(n, r - 1, str + '1')
}

var n = 5;
var sol = S(n, 2 ** n - n, '0'.repeat(n));
console.log('Solution: ' +  sol)
console.log('Count: ' + count);

var end = +new Date();
console.log((end - start)/1000 + ' seconds to run');
