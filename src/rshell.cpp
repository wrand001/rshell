#include <iostream>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <sys/wait.h>
#include <cstring>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

#define READ 0      //for piping processes
#define WRITE 1     //also for piping processes

using namespace std;
bool prompt();
bool splitinput(string userIn);
void split(string s, string delimiter, vector<string> &tokens);
bool processinput(char **arguments);
void fixwrapper(string &s, char firstwrap, char secwrap, string commandreplace);
void spacetrim(string &s);
bool exetest(char** arguments);
bool processinputnest(string &commands, bool &exiting);


int main(int argc, char *argv[])
{
    while(true)
    {
        if(prompt())
        {
            cout<<"EXITING"<<endl;
            break;
        }
    }
    return 0;
}

bool prompt() //only prints prompt and puts input into a string. calls processinput
{
    const int CHARSIZE = 255;
    string logID;
    char hostID[CHARSIZE];
    logID = getlogin();
    gethostname(hostID, CHARSIZE);
    cout<<logID<<"@"<<hostID<<"$ "; //printing login and hostname before input
    string userIn;
    getline(cin,userIn);
    if(splitinput(userIn))
    {
        return true;
    }
    return false;
}

bool splitinput(string userIn) //just splits input into digestible chunks for processinput, no real validation
{
    vector<string> nocomments;
    bool exitflag = false;
    bool doneflag = false;

    //cout<<endl<<"spliting by #"<<endl;
    split(userIn, "#", nocomments); //split first by #, then (), then ;, then &&, then ||, then space
    string theCommands = nocomments.at(0);
    nocomments.clear();
    size_t pone = 0, ptwo = 0;
    while(string::npos != pone && string::npos != ptwo)
    {
        pone = theCommands.find('(', ptwo);
        if(string::npos != pone)
        {
            ptwo = theCommands.find(')', pone);
            if(string::npos != ptwo)
            {
                doneflag = false;
                string sub = theCommands.substr(pone, ptwo+1 - pone);
                string sub2 =sub.substr(1, sub.length() - 2 );
                spacetrim(sub2);
                if(processinputnest(sub2, exitflag))
                {
                    theCommands.replace(theCommands.find(sub), sub.length(), "false");
                }
                else
                {
                    theCommands.replace(theCommands.find(sub), sub.length(), "true");
                }
                if(exitflag)
                {
                    return true;
                }
            }
            else
            {
                if(doneflag)
                {
                    break;
                }
            }

        }
        else
        {
            if(doneflag)
            {
                break;
            }
        }
        processinputnest(theCommands, exitflag);
        doneflag = true;
        if(exitflag)
        {
            return true;
        }
    }
    return false;
}

void split(string s, string delimiter, vector<string> &tokenVector)
{
    //cout<<"string to split: "<<s<<endl;
    if(s.find(delimiter) != string::npos)
    {
        s.append(delimiter);
        size_t pos = 0;
        string token;
        while((pos = s.find(delimiter)) != string::npos)
        {
            token = s.substr(0, pos);
            spacetrim(token);
            tokenVector.push_back(token);
            s.erase(0, pos + delimiter.length());
        }
    }
    else
    {
        tokenVector.push_back(s);
    }
}

bool processinput(char** arguments)
{
    pid_t pid;
    int status;
    if((pid = fork()) < 0)
    {
        perror("fork failed.");
        return 1;
    }
    if (pid > 0) //parent process
    {
        while(wait(&status) != pid);
    }
    else //child process
    {
        if(strcmp(arguments[0], "true") == 0) // if command is true
        {
            exit(0);
            return 0;
        }
        if(strcmp(arguments[0], "false") == 0) // if command is false
        {
            exit(1);
            return 1;
        }
        else if(strcmp(arguments[0], "test") == 0) //use rshell's test command
        {
            exit(1);
            return exetest(arguments);
        }
        else if(execvp(arguments[0], arguments) < 0) //use bin for other commands
        {
	    perror("command failed.");
            exit(1);
            return 1;
        }
    }
    return 0;
}

void fixwrapper(string &s, char firstwrap, char secwrap, string commandreplace)
{
    size_t findex = 0, sindex = 0;
   while(string::npos != sindex && string::npos != findex)
   {
       findex = s.find(firstwrap, sindex);
       if(string::npos != findex)
       {
            sindex = s.find(secwrap, findex);
            if(string::npos != sindex)
            {
                string sub = s.substr(findex, sindex+1);
                string sub2 = s.substr(findex+1, sindex-1);
                spacetrim(sub2);
                sub2 = commandreplace + " " + sub2;
                s.replace(s.find(sub), sub.length(), sub2);
            }
       }
   }
}

void spacetrim(string &s)
{
    size_t endpos = s.find_last_not_of(" \t");
    if( string::npos != endpos )
    {
        s = s.substr( 0, endpos+1 );
    }
    size_t startpos = s.find_first_not_of(" \t");
    if( string::npos != startpos )
    {
        s = s.substr( startpos );
    }
}

bool exetest(char** arguments) //rshell's test command
{
    int starti = 1;
    if(arguments[starti] == NULL)
    {
        return 1;
    }
    if(arguments[1][0] == '-' && arguments[starti+1] != NULL)
    {
        struct stat buffer;
        stat(arguments[starti+1], &buffer);
        switch(arguments[1][1])
        {
        case 'f':
            if(S_ISREG(buffer.st_mode))
            {
                return 0;
            }
            return 1;
        case 'd':
            if(S_ISDIR(buffer.st_mode))
            {
                return 0;
            }
            return 1;
        case 'e':
            if(S_ISDIR(buffer.st_mode) || S_ISREG(buffer.st_mode))
            {
                return 0;
            }
            return 1;
        default:
            perror("unknown flag for test.");
            return 1;
        }
    }
    struct stat buffer;
    stat(arguments[starti], &buffer);
    if(S_ISDIR(buffer.st_mode) || S_ISREG(buffer.st_mode))
    {
        return 0;
    }
    return 1;
}

bool processinputnest(string &commands, bool &exiting)
{
    vector<string> colonsplit;
    vector<string> andsplit;
    vector<string> pipesplit;
    bool connectflag = false;
    int pipecounter = 0;

    split(commands, ";", colonsplit);
    for(vector<string>::iterator CSit = colonsplit.begin(); CSit != colonsplit.end(); ++CSit)
    {
        connectflag = false;
        fixwrapper(*CSit, '[', ']', "test");
        andsplit.clear();
        //cout<<endl<<"spliting by &&"<<endl;
        split (*CSit, "&&", andsplit);

        for(vector<string>::iterator ASit = andsplit.begin(); ASit != andsplit.end(); ++ASit)
        {
            pipesplit.clear();
            //cout<<endl<<"spliting by ||"<<endl;
            split (*ASit, "||", pipesplit);
            char* argu;
            char* tok;
            pipecounter = 0;
            for(vector<string>::iterator PSit = pipesplit.begin(); PSit != pipesplit.end(); ++PSit)
            {
                if(pipecounter > 0)
                {
                    connectflag = !connectflag;
                }
                pipecounter++;
                char* arguments[255];
                argu = (char *) malloc((*PSit).length()+1);
                for(unsigned int i = 0; i < (*PSit).length(); ++i)
                {
                    argu[i] = (*PSit).at(i);
                }
                argu[(*PSit).length()] = '\0';
                tok = strtok(argu, " ");

                int i = 0;
                while(tok != NULL)
                {
                    if(!strcmp(tok, "exit"))
                    {
                        exiting = true;
                        break;
                    }
                    arguments[i++] = tok;
                    tok = strtok(NULL, " ");
                }
                arguments[i] = NULL;
                if(!exiting && !connectflag)
                {
                    connectflag = processinput(arguments); //process input does validation
                    //true = process went bad
                    //false = process is ok
                    //connect flag is for connectors
                }
                else
                {
                    connectflag = true;
                }
                free(argu);
            }
            if(exiting)
            {
                break;
            }

        }
        if(exiting)
        {
            break;
        }
    }
    return connectflag;
}
