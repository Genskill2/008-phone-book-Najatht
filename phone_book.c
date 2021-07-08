entry *
load_entries(FILE *fp) {
  char name[20], phone[20];
  memset(name, '\0', 20);
  memset(phone, '\0', 20);
  entry *ret = NULL;
  entry *current = NULL;
  entry *tmp = NULL;
  /* Description of %20[^,\n]
     % is the start of the specifier (like %s, %i etc.)
     20 is the maximum number of characters that this will take. We
        know that names and phone numbers will be 20 bytes maximum so
        we limit it to that. %20s will read in 20 character strings
        (including the , to separate the name and phone number. That's
        why we use
    [^,\n] Square brackets are used to indicate a set of allowed
           characters [abc] means only a, b, or c. With the ^, it's
           used to specify a set of disallowed characters. So [^abc]
           means any character *except* a, b, or c. [^,] means any
           character except a , [^,\n] means any character except a
           comma(,) or a newline(\n).
    %20[^,\n] will match a string of characters with a maximum length
     of 20 characters that doesn't have a comma(,) or a newline(\n).
  */        
  while (fscanf(fp, "%20[^,\n],%20[^,\n]\n", name, phone) != EOF) {
    tmp = create_entry_node(name, phone);
    if (ret == NULL)
      ret = tmp;
    else
      current->next = tmp;
    current = tmp;
  }
  return ret;
}

void write_all_entries(entry * p) {
  FILE *fp = fopen(DB, "w");
  while (p != NULL) {
    fprintf(fp, "%s,%s\n", p->name, p->phone);
    p = p->next;
  }
  fclose(fp);
}


void add(char *name, char *phone) {
  FILE *fp = fopen(DB, "a");
  fprintf(fp, "%s,%s\n", name, phone);
  fclose(fp);
}
int search(FILE *db_file,char *name){
  entry *p = load_entries(db_file);
  entry *base = p;
  int found = 0;
  while(p!=NULL){
  if(strcmp(p->name,name) == 0){
  printf("%s\n",p->phone);
 
  found = 1;
  }
   p=p->next;
  }
  free_entries(base);
  return found;
}

int size = 0;
void list(FILE *db_file) {
  entry *p = load_entries(db_file);
  entry *base = p;
  int count = 0;
  while (p!=NULL) {
    printf("%-20s : %10s\n", p->name, p->phone);
    count++;
    p=p->next;
  }
  /* TBD print total count */
  size =count;
  printf("Total entries :  %d\n",count);
  free_entries(base);
 
}


int delete(FILE *db_file, char *name) {
  entry *p = load_entries(db_file);
  entry *base = p;
  entry *prev = NULL;
  entry *del = NULL ; /* Node to be deleted */
  int deleted = 0;

  while (p!=NULL) {
    if (strcmp(p->name, name) == 0) {
      /* Matching node found. Delete it from the linked list.
         Deletion from a linked list like this
   
             p0 -> p1 -> p2
         
         means we have to make p0->next point directly to p2. The p1
         "node" is removed and free'd.
         
         If the node to be deleted is p0, it's a special case. 
      */

      /* TBD */
      
       if(strcmp(base->name, name) == 0){
         base = p->next;
       }
      else{ p = p->next;
      
       prev->next = p;
          }
      
       deleted = 1;
       break;
    }
    else{
      prev = p;
      p = p->next;
    }
   
  }
  write_all_entries(base);
  free_entries(base);
  return deleted;
}
