var start = new Date().getTime();

var d = {};
var count = 0;
var nums = [];

function reverse(n) {
    var c = 0;
    while (n != 0) {
        c = 10 * c + n % 10
        n = (n / 10) >> 0;
    }
    return c;
}

main_loop:
for (var s = 1; s < 30000; s++) {
    for (var c = 1; c < 5000; c++) {
        var n = s*s + c*c*c;
        var rev = reverse(n);
        if (n == rev) {
            if (n in d) {
                d[n] += 1;
                if (d[n] == 4) {
                    count += 1
                    nums.push(n);
                    if (count >= 5) {
                        break main_loop;
                    }
                }
            } else {
                d[n] = 1;
            }
        }
    }
}

console.log(nums);
var sum = nums.reduce((x, y) => x + y, 0);
console.log('Solution: ' +  sum);


var end = new Date().getTime();
console.log(`${(end - start)/1000} seconds to run`)
