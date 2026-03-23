#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void print_indent(int depth){
  for(int i = 0; i < depth; i++)
    printf("  ");
}

void tree(char *path, int depth){
  int fd;
  struct stat st;
  struct dirent de;
  char buf[512], *p;

  if((fd = open(path, 0)) < 0){
    printf("tree: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    printf("tree: cannot stat %s\n", path);
    close(fd);
    return;
  }

  // Print current directory/file name only
  char *name = path;
  for(int i = strlen(path)-1; i >= 0; i--){
    if(path[i] == '/'){
      name = path + i + 1;
      break;
    }
  }

  print_indent(depth);
  printf("%s", name);
  if(st.type == T_DIR)
    printf("/\n");
  else{
    printf("\n");
    close(fd);
    return;
  }

  // Prepare buffer
  if(strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)){
    printf("tree: path too long\n");
    close(fd);
    return;
  }

  strcpy(buf, path);
  p = buf + strlen(buf);
  *p++ = '/';

  while(read(fd, &de, sizeof(de)) == sizeof(de)){
    if(de.inum == 0)
      continue;

    char child[DIRSIZ+1];
    memmove(child, de.name, DIRSIZ);
    child[DIRSIZ] = 0;

    if(strcmp(child, ".") == 0 || strcmp(child, "..") == 0)
      continue;

    memmove(p, child, strlen(child)+1);

    if(stat(buf, &st) < 0){
      printf("tree: cannot stat %s\n", buf);
      continue;
    }

    tree(buf, depth + 1);
  }

  close(fd);
}

int main(int argc, char *argv[]){
  if(argc == 1)
    tree(".", 0);
  else
    tree(argv[1], 0);
  exit(0);
}
