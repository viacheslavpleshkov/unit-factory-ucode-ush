#include "libmx.h"

void *mx_realloc(void *ptr, size_t size){
   void *new_ptr;

   if (!ptr) {
      new_ptr = malloc(size);
      if(!new_ptr) return NULL;
      return new_ptr;
   }
   if (malloc_size(ptr) < size) {
      new_ptr = malloc(size);
      if (!new_ptr) return NULL;
      mx_memcpy(new_ptr, ptr, malloc_size(ptr));
      free(ptr);
   }
   else new_ptr = ptr;
   return new_ptr;
}
