 #include <cstddef>

template <class T>
struct List {
    T val;
    List<T>* next;
};

template <class T>
struct Vec {
    T* data;
    size_t s, cap;
};

template <class T>
Vec<List<T>*> balanced_copy(Vec<List<T>*> v, size_t k) {
    size_t total = 0;
    for (size_t i = 0; i < v.s; i++) {
        List<T>* current = v.data[i];
        while (current) {
            total++;
            current = current->next;
        }
    }
    
    size_t base = total / k;
    size_t resto = total % k;
    
    Vec<List<T>*> res;
    res.s = k;
    res.cap = k;
    res.data = new List<T>*[k];
    
    for (size_t i = 0; i < k; i++) {
        res.data[i] = nullptr;
    }
    
    size_t idx_lista = 0;
    size_t contador = 0;
    List<T>** ultimo = &res.data[0];
    
    for (size_t i = 0; i < v.s; i++) {
        List<T>* current = v.data[i];
        while (current) {
            List<T>* novo = new List<T>;
            novo->val = current->val;
            novo->next = nullptr;
            
            *ultimo = novo;
            ultimo = &(novo->next);
            
            contador++;
            
            size_t limite = base + (idx_lista < resto ? 1 : 0);
            if (contador >= limite && idx_lista < k - 1) {
                idx_lista++;
                contador = 0;
                ultimo = &res.data[idx_lista];
            }
            
            current = current->next;
        }
    }
    
    return res;
}