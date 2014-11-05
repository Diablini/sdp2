

template<typename T>
struct node
{
	node() {
		data = NULL;
		next = NULL;
	}
	node(T& data, node<T> * next) {
		this->data = data;
		this->next = next;
	}
	node(const node<T> & c) {
		this->data = c.data;
	}
	~node() {
		delete data;
		delete next;
	}

private:
	T * data;
	node<T> * next;

	template<typename T>
	friend class List;
};

template<typename T>
class List
{
public:
	List() {
		first = new node<T>();
		last = NULL;
		size = 0;
	}
	~List() {
		delete first;
	}
	node<T> & getAt(size_t pos) {
		node * current = first->next;
		register size_t counter = pos;
		while(counter > 0) {
			current = current.next;
			counter--;
		}
		return *current;
	}
	void insert(T & data, size_t pos) {
		node<T> * my = getAt(pos);
		node<T> * toinsert = new node<T> (data, my->next);
		my->next = &toinsert;
	}

private:
	node<T> * first, *last;
	size_t size;

};