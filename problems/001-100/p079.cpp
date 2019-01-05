#include "lib/utility.hh"

using dependency_graph = std::unordered_map<char, std::unordered_set<char>>;

dependency_graph build_dep_graph() {
    std::ifstream ifs("files/p079_keylog.txt");
    if (!ifs.good()) {
        throw std::runtime_error("unable to open 'files/p079_keylog.txt'");
    }

    dependency_graph graph;
    std::string line;
    while (ifs >> line) {
        for (size_t i = 0; i < line.size(); ++i) {
            if (!graph.count(line[i])) {
                graph[line[i]] = {};
            }
            for (size_t j = 0; j < i; ++j) {
                graph[line[i]].insert(line[j]);
            }
        }
    }
    return graph;
}

std::string build_passcode(dependency_graph graph) {
    std::string passcode = "";
    while (graph.size() > 0) {
        for (const auto& [digit, dependencies] : graph) {
            if (dependencies.empty()) {
                passcode += digit;
                for (auto& [_, other_deps] : graph) {
                    other_deps.erase(digit);
                }
                graph.erase(digit);
                break;
            }
        }
    }
    return passcode;
}

int main(void) {
    start_time();
    dependency_graph dep_graph = build_dep_graph();
    std::cout << "Solution: " << build_passcode(dep_graph) << std::endl;
    end_time();
}
