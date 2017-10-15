open Printf ;;

let tbl = Hashtbl.create 10000 ;;
let rec w prev acc max_r r c =
    let key = (prev, acc, r, c) in
    try Hashtbl.find tbl key
    with Not_found ->
        if r = 0 && c = 1 then 1
        else if r < 0 || c <= 0 then 0
        else if r = 0 && c > 1 then w acc [] max_r max_r (c - 1)
        else
            let try_path n =
                let a = r - n in
                if a = 0 || not (List.mem a prev) then
                    w prev (a :: acc) max_r a c
                else 0 in
            let tot = (try_path 2) + (try_path 3) in
            let _ = Hashtbl.add tbl key tot in
            tot
;;

let main r c = w [] [] r r c ;;

let _ =
    let start = Sys.time () in
  let argi n = int_of_string Sys.argv.(n) in
  let _ = printf "Solution: %d\n" (main (argi 1) (argi 2)) in
  let finish = Sys.time () in
  printf "%f seconds to run\n" (finish -. start)
