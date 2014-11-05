
const size_t INIT_QUEUE_SIZE = 32;
const size_t INIT_QUEUE_POS = 16;

template <typename T>
class Queue
{
public:
	Queue() {
		queue = new T [INIT_QUEUE_SIZE];
		head = INIT_QUEUE_POS;
		tail = NULL;
		elements = 0;
		capacity = INIT_QUEUE_SIZE;

	}
	~Queue() {
		delete [] queue;
	}
	void enqueue(T& what) {
		if (elements != 0 || head == tail) resize();
		
	}
	
private:

	size_t head;
	size_t tail;
	size_t elements;
	size_t capacity;
	T * queue;
	void resize();
};
