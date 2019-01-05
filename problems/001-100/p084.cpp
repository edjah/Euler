#include "lib/utility.hh"

std::array<std::string, 40> board = {
    "GO", "A1", "CC1", "A2", "T1", "R1", "B1", "CH1", "B2", "B3", "JAIL",
    "C1", "U1", "C2", "C3", "R2", "D1", "CC2", "D2", "D3", "FP",
    "E1", "CH2", "E2", "E3", "R3", "F1", "F2", "U2", "F3", "G2J",
    "G1", "G2", "CC3", "G3", "R4", "CH3", "H1", "T2", "H2"
};

std::unordered_map<std::string, int> name_to_board_pos;

std::array<std::string, 16> community_chest = {
    "GO", "JAIL"
};

std::array<std::string, 16> chance = {
    "GO", "JAIL", "C1", "E3", "H2", "R1", "_nextR", "_nextR",
    "_nextU", "_back3"
};

std::array<int, 40> move_counts;

int cc_pos = 0;
int chance_pos = 0;

int move(int pos, int double_count = 0) {
    int r1 = 1 + (rand() % 4);
    int r2 = 1 + (rand() % 4);

    if (r1 == r2 && double_count == 2) {
        return name_to_board_pos["JAIL"];
    }

    pos = (pos + r1 + r2) % board.size();

    std::string action = "";
    if (starts_with(board[pos], "CC")) {
        action = community_chest[cc_pos];
        cc_pos = (cc_pos + 1) % community_chest.size();
    } else if (starts_with(board[pos], "CH")) {
        action = chance[chance_pos];
        chance_pos = (chance_pos + 1) % chance.size();
    } else if (board[pos] == "G2J") {
        action = "JAIL";
    }

    if (name_to_board_pos.count(action)) {
        pos = name_to_board_pos[action];
        if (action == "JAIL") {
            return pos;
        }
    } else if (starts_with(action, "_next")) {
        std::string search_key(1, action[5]);
        while (!starts_with(board[pos], search_key)) {
            pos = (pos + 1) % board.size();
        }
    } else if (action == "_back3") {
        pos = (pos - 3) % board.size();
        if (starts_with(board[pos], "CC")) {
            action = community_chest[cc_pos];
            cc_pos = (cc_pos + 1) % community_chest.size();
            if (name_to_board_pos.count(action)) {
                pos = name_to_board_pos[action];
            }
        }
    }

    if (r1 == r2) {
        return move(pos, double_count + 1);
    }
    return pos;
}

std::string monopoly_odds(int num_trials) {
    random_shuffle(community_chest);
    random_shuffle(chance);

    for (size_t i = 0; i < board.size(); ++i) {
        name_to_board_pos[board[i]] = i;
    }

    int pos = 0;
    for (int i = 0; i < num_trials; ++i) {
        pos = move(pos);
        move_counts[pos] += 1;
    }

    std::vector<std::pair<int, int>> freqs;
    for (size_t i = 0; i < board.size(); ++i) {
        freqs.push_back({move_counts[i], i});
    }
    std::sort(freqs.begin(), freqs.end());
    std::reverse(freqs.begin(), freqs.end());
    for (size_t i = 0; i < board.size(); ++i) {
        printf("%s | %02d | %.4f\n", +board[freqs[i].second],
               freqs[i].second, 1.0 * freqs[i].first / num_trials);
    }

    char buf[64];
    sprintf(buf, "%02d%02d%02d", freqs[0].second,
            freqs[1].second, freqs[2].second);
    return std::string(buf);
}

int main(void) {
    start_time();
    printf("Solution: %s\n", +monopoly_odds(10000000));
    end_time();
}
