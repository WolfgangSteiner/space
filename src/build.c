#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

typedef struct
{
    bool debug;
} Arguments;


Arguments* parse_command_line(int argc, char** argv)
{
    Arguments* args = calloc(1, sizeof(Arguments));

    for (int i = 1; i < argc; ++i)
    {
        char* argument = argv[i];

        if (!strcmp(argument, "--debug"))
        {
            args->debug = true;
        }
    }

    return args;
}


int main(int argc, char** argv)
{
    Arguments* args = parse_command_line(argc, argv);

    char cmd[1024];
    system("mkdir -p bin");

    const char* exec_name = "space"; 
    const char* src_files = "src/build_dependencies.c"; 
    const char* build_options = args->debug ? "-g" : "-O2";
    const char* warnings = "-Wall -Werror -Wextra";
    const char* include_dirs = "-Isrc";
    const char* link_libraries = "-lm -lSDL2";
    int result = 1;

    snprintf(cmd, 1024, "gcc %s %s %s %s -o bin/%s %s",
            build_options, warnings, include_dirs, link_libraries, exec_name, src_files);

    while ((result = system(cmd)))
    {
        sleep(1);
    }

    if (result == 0)
    {
        if (args->debug)
        {
            snprintf(cmd, 1024, "lldb bin/%s", exec_name);
        }
        else
        {
            snprintf(cmd, 1024, "bin/%s", exec_name);
        }

        system(cmd);
    }

}
