#include "StateQueue.h"

StateQueue::StateQueue() {
	reset();
}

StateQueue::~StateQueue() {
	// TODO Auto-generated destructor stub
}

void StateQueue::reset() {
	length_ = 0;
	for (unsigned int i = 0; i < queue_.size(); ++i) {
		queue_[i].reset();
	}
}

void StateQueue::add_state(xState x) {

	std::cout << "Adding state: " << x.x_ << "," << x.y_ << std::endl;

	queue_[length_] = x;
	length_++;

	std::cout << "Updated Queue:" << std::endl;
	printQueue();
}

xState StateQueue::get_first(){

	xState returnValue = queue_[0];

	for (unsigned int i = 0; i < length_ - 1; ++i) {
		queue_[i] = queue_[i + 1];
	}
	queue_[length_].reset();
	--length_;

	std::cout << "Getting first: " << returnValue.x_ << "," << returnValue.y_ << " Length: " << length_ << std::endl;

	return returnValue;
}

unsigned int StateQueue::get_length() {
	return length_;
}

void StateQueue::printQueue() {
	for (unsigned int i = 0; i < queue_.size(); ++i){
		std::cout << "  " <<  queue_[i].x_ << "," << queue_[i].y_ << "(" << queue_[i].printState() << ")";
	}
	std::cout << std::endl;
}
