#include <queue> 
#include <dirent.h> 
#include <iostream> 
#include <string> 
#include <vector> 

using namespace std; 

class Directory
{
    public: 
        Directory(const string& _path) { 
            path = _path; 
            pdir = opendir(path.c_str()); 
        }

        Directory(Directory&& other) { 
            pdir = other.pdir;
            path = other.path; 
            other.pdir = nullptr;  
            other.path = ""; 
        }

        Directory(Directory& other) { 
            pdir = other.pdir; 
            path = other.path; 
            other.pdir = nullptr; 
        }

        ~Directory() 
        {
            if (pdir) 
               closedir(pdir);  
        }

        bool isopen() 
        {
           return (pdir != nullptr);  
        }

        struct dirent* get_next() 
        {
           return readdir(pdir);  
        }

        string get_name() 
        {
           return path;  
        }

    private:  
        string path = ""; 
        DIR* pdir = nullptr; 
}; 

int main()
{
    Directory dir("."); 

    if (!dir.isopen()) { 
        printf("unable to open current working directory\n");
    }

    std::queue<Directory> q_dirs;
    q_dirs.push(move(dir)); 
 
    while (!q_dirs.empty()) { 
        Directory cdir = move(q_dirs.front()); 
        q_dirs.pop(); 
        string currpath = cdir.get_name(); 
    
        if (!cdir.isopen()) 
        {
            printf("unable to open dir %s\n", currpath.c_str()); 
            continue; 
        }

        printf("%s\n", currpath.c_str()); 
        struct dirent* t; 
        
        while ((t = cdir.get_next()) != nullptr) { 
            string filename = string(t->d_name);

            if ((filename == ".") || (filename == "..") || (filename == ".git"))
                    continue;

            printf("\t%s\n", t->d_name); 

            if (t->d_type == DT_DIR) {
                q_dirs.emplace(Directory(currpath + "/" + filename)); 
            }
        }

        printf("\n"); 
    } 
     
    return 0;  
}
