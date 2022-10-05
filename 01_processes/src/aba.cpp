#include <iostream>
#include <unistd.h> // fork
#include <chrono>
#include <thread>
#include <csignal>
#include <sys/wait.h>

using namespace std;

string getChars(const char* envVariable, string defaultVal) {
    char* letters = getenv(envVariable);
    if (letters == nullptr) {
        return defaultVal;
    }
    return string(letters);
}

int main() {
    cout << "waiting for 3 seconds" << endl;
    auto pid{fork()};
    pid_t pid2;
    string defaultVal = "A";
    string envVar = "ABA_LETTER_A";
    if(pid != 0) {
        defaultVal = "B";
        envVar = "ABA_LETTER_B";
        pid2 = fork();
    } 
    int counter = 0;
    chrono::milliseconds sleeptime(500);
    if (pid != 0 && pid2 != 0) {
        while(counter < 6) {
            this_thread::sleep_for(sleeptime);
            counter++;
        }
        cout << endl;
        cout << "killing both subprocesses with pids " 
        << pid << " and " << pid2 << endl;
        kill(pid, SIGKILL);
        kill(pid2, SIGKILL);
        int status;
        int status2;
        waitpid(pid, &status, 0);
        waitpid(pid2, &status2, 0);
        cout << "waiting for both subprocesses to be dead" << endl;
        cout << "subprocess " << pid << " exited with " << WIFEXITED(status) << endl;
        cout << "subprocess " << pid2 << " exited with " << WIFEXITED(status2) << endl;
    } else {
        string letter{getChars(envVar.c_str(), defaultVal)};
        errno = execl("./charout", letter.c_str(), nullptr);
        if (errno == -1) {
            cerr << "starting charout failed: No such file or directory" << endl;
        }
        exit(1);

    } 
}
