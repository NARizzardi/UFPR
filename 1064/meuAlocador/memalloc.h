void *topo_inicial_heap;
void setup_brk();
void dismiss_brk();
void* memory_alloc(unsigned long int bytes);
int memory_free(void *pointer);
void memory_mapping();