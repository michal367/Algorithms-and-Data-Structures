template<class W>
class IndexedPQ{ // indexed min priority queue for Dijkstra algorithm
    std::size_t size;
    std::size_t* h;     // heap containing graph vertices
    std::size_t* hp;    // position of graph vertex in heap
    W* dist;            // key (priority)

public:
    IndexedPQ(std::size_t s){
        size = 0;
        h = new std::size_t[s];
        hp = new std::size_t[s];
        for(std::size_t i=0; i<s; i++)
            hp[i] = -1;
        dist = new W[s];
    }
    ~IndexedPQ(){
        delete[] h;
        delete[] hp;
        delete[] dist;
    }
    void push(std::size_t v, W d){
        h[size] = v;
        dist[v] = d;
        hp[v] = size;
        size++;
        std::size_t child = hp[v];
        std::size_t parent = (child-1)/2;
        while(child != 0 && dist[h[parent]] > dist[v]){
            std::swap(hp[v], hp[h[parent]]);
            std::swap(h[child], h[parent]);
            child = parent;
            parent = (child-1)/2;
        }
    }
    std::size_t pop(){
        if(size > 0){
            std::size_t t = h[0];
            hp[h[0]] = -1;
            --size;
            if(size > 0){
                h[0] = h[size];
                hp[h[size]] = 0;
                std::size_t pos = 0;
                do{
                    std::size_t left = 2*pos+1;
                    std::size_t right = left+1;
                    if(left < size && dist[h[left]] < dist[h[pos]]){
                        std::swap(hp[h[left]], hp[h[pos]]);
                        std::swap(h[left], h[pos]);
                        pos = left;
                    }
                    else if(right < size && dist[h[right]] < dist[h[pos]]){
                        std::swap(hp[h[right]], hp[h[pos]]);
                        std::swap(h[right], h[pos]);
                        pos = right;
                    }
                    else
                        break;
                }while(true);
            }
            return t;
        }
        return -1;
    }
    void decrease_key(std::size_t v, W d){
        dist[v] = d;
        std::size_t child = hp[v];
        std::size_t parent = (child-1)/2;
        while(child != 0 && dist[h[parent]] > dist[v]){
            std::swap(hp[v], hp[h[parent]]);
            std::swap(h[child], h[parent]);
            child = parent;
            parent = (child-1)/2;
        }
    }
    bool contains(std::size_t v){
        return (hp[v] != -1);
    }
    bool empty(){
        return (size == 0);
    }
};
