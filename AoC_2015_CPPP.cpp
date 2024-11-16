#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace solution_6_1 {

struct Instruction {
    std::string instruction;
    int x1;
    int y1;
    int x2;
    int y2;
} ;

std::vector<std::string> get_input() {
    std::vector<std::string> content;
    std::ifstream file("input_6.txt"); 
    std::string line;
    while (std::getline(file, line)) { 
        content.push_back(line);
    }
    file.close(); 
    return content;
}

Instruction get_instruction(std::string str) {
    Instruction ins {};
    // instruction
    int start = 0;
    int end = str.find(' ', start);
    ins.instruction = str.substr(start, end - start);
    if (ins.instruction =="turn") {
        start = end + 1;
        end = str.find(' ', start);
        ins.instruction = str.substr(start, end - start);
    }
    // x1 und y1
    start = end + 1;
    end = str.find(' ', start);
    std::string temp = str.substr(start, end - start);
    int start2 = 0;
    int end2 = temp.find(',', start2);
    ins.x1 = std::stoi(temp.substr(start2, end2 - start2));
    start2 = end2 + 1;
    end2 = temp.find(',', start2);
    ins.y1 = std::stoi(temp.substr(start2, end2 - start2));
    // through
    start = end + 1;
    end = str.find(' ', start);
    temp = str.substr(start, end - start);
    // x2 und y2
    start = end + 1;
    end = str.find(' ', start);
    temp = str.substr(start, end - start);
    start2 = 0;
    end2 = temp.find(',', start2);
    ins.x2 = std::stoi(temp.substr(start2, end2 - start2));
    start2 = end2 + 1;
    end2 = temp.find(',', start2);
    ins.y2 = std::stoi(temp.substr(start2, end2 - start2));
    return ins;
}

void setLight(bool (&matrix)[1000][1000], std::string ins, int y, int x) {
    if (ins == "toggle") {
        if (matrix[y][x]) matrix[y][x] = false;
        else matrix[y][x] = true;    
    }
    else if (ins == "on") matrix[y][x] = true;
    else matrix[y][x] = false;
}

void setLights(bool (&matrix)[1000][1000], const Instruction & ins) {
    for (int i = ins.y1; i <= ins.y2; i++) {
        for (int j = ins.x1; j <= ins.x2; j++) {
                setLight(matrix, ins.instruction, i, j);
        }
    }       
}

int countLights(const bool (&matrix)[1000][1000]) {
    int counter {};
    for (int i = 0; i <= 999; i++) {
        for (int j = 0; j <= 999; j++) {
            if (matrix[i][j]) counter++;
        }
    }
    return counter;
}

void solution() {
    bool matrix[1000][1000] {};
    std::vector<std::string> content = get_input();  
    for (std::string line : content) {
        Instruction ins = get_instruction(line);
        setLights(matrix, ins); 
    } 
    std::cout << countLights(matrix) << "\n";
}

}
