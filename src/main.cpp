#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "version.h"
#include "functions.h"

int isPropmptActive = 0; 

void print_help();
void print_version();

int execute(const std::string& command);
void execute_file(const std::string& filepath);

void command_prompt();

int main(int argc, char *argv[]) {
    
    if (argc == 1) {
        isPropmptActive = 1;
        command_prompt();
    }
    else if (strcmp(argv[1], "-h") == 0) {
        print_help();
    }
    else if (strcmp(argv[1], "-v") == 0) {
        print_version();
    }
    else if (argc > 1) {
        execute_file(argv[1]);
    }

    return 0;
}

void print_help() {
    printf("Commands:\n");
    printf("\t-h: Show this message\n");
    printf("\t-v: Show current glib interpreter version\n");
    printf("\t<file>: Execute with <file>\n");
}

void print_version() {
    printf("Glib %s", GL_VERSION);
}

int execute(const std::string& command, const int& line) {
    std::string tmp; 
    std::stringstream ss(command);
    std::vector<std::string> tokens;

    while(std::getline(ss, tmp, ' ')){
        tokens.push_back(tmp);
    }

    if (tokens[0] == "push") {
        if (tokens.size() == 1) {
            GL_SYNTAX_ERROR_MSG("No argument given", tokens[0].c_str(), line);
        } else {
            gl_push(std::stoi(tokens[1]));
        }
    }
    else if (tokens[0] == "print") {
        gl_print();
    }
    else if (tokens[0] == "printc") {
        gl_printc();
        if (isPropmptActive == 1) {
            printf("\n");
        }
    }
    else if (tokens[0] == "input") {
        if (isPropmptActive == 0)
            gl_input();
        else
            GL_SYNTAX_ERROR_MSG("input is only available for files", tokens[0].c_str(), line);
    }
    else if (tokens[0] == "inputc") {
        if (isPropmptActive == 0)
            gl_inputc();
        else
            GL_SYNTAX_ERROR_MSG("input is only available for files", tokens[0].c_str(), line);
    }
    else if (tokens[0] == "pop") {
        gl_pop();
    }
    else if (tokens[0] == "add") {
        gl_add();
    }
    else if (tokens[0] == "sub") {
        gl_sub();
    }
    else if (tokens[0] == "inc") {
        gl_inc();
    }
    else if (tokens[0] == "dec") {
        gl_dec();
    }
    else if (tokens[0] == "mul") {
        gl_mul();
    }
    else if (tokens[0] == "dup") {
        gl_dup();
    } 
    else if (tokens[0] == "jmp") {
        if (tokens.size() == 1) {
            GL_SYNTAX_ERROR_MSG("No argument given", tokens[0].c_str(), line);
        } else {
            return std::stoi(tokens[1]);
        }
    }
    else if (tokens[0] == "ifeq") {
        if (tokens.size() != 3) {
            GL_SYNTAX_ERROR_MSG("Invalid argument count given", tokens[0].c_str(), line);
        } else {
            if (gl_peek() == stoi(tokens[1])) {
                // Continue
            } else 
                return std::stoi(tokens[2]);
        }
    }
    else if (tokens[0][0] == '/' && tokens[0][1] == '/') {
        // comment, do nothing
        return -1;
    }
    else {
        GL_SYNTAX_ERROR_MSG("Unknown token", tokens[0].c_str(), line);
    }

    return -1;
}

void execute_file(const std::string& filepath) {
    std::ifstream file;
    file.open(filepath);

    if (file.is_open()) {
        std::string line;
        std::vector<std::string> lines;
        while (std::getline(file, line))
        {
            lines.emplace_back(line);
        }
        file.close();

        for (int i = 0; i < lines.size(); i++) {
            int n = execute(lines[i], i+1);
            if (n > 0) {
                i = n-2;
            }
        }
    } else {
        GL_FILE_ERROR_MSG("Cannot open file", filepath.c_str());
    }
}

void command_prompt() {
    while (isPropmptActive == 1) {
        printf("> ");
        std::string command;
        std::getline(std::cin, command);
        if (command != "exit")
            execute(command, 0);
        else
            isPropmptActive = 0;
    }
}