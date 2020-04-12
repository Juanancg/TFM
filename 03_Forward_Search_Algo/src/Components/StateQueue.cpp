#include "src/Components/StateQueue.h"
#include "src/Utils/basic_functions.h"
#include <iomanip>
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

	std::cout << "Updated Queue: " << length_ << std::endl;
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

xState StateQueue::get_first(const xState goalState) {

	xState returnValue;
	double distance = 0;
	double temp_distance = 0;
	bool first_distance = true;
	int near_point = 0;

	for (unsigned int i = 0; i < length_; ++i) {
		if (queue_[i].state_ == E_STATE_VISITED) {
			std::cout << i << " | " ;
			temp_distance = get_distance(goalState, queue_[i]);
std::cout << " ~~ Visited  d = " <<std::setprecision(6)<< temp_distance << "   | " << std::endl;;

			if (first_distance || temp_distance < distance) {
				distance = temp_distance;
				near_point = i;
				first_distance = false;
			}
		}
	}

	returnValue = queue_[near_point];
	queue_[near_point].reset();
	--length_;

	std::cout << "Getting near: i = " << near_point << " | " << returnValue.x_ << "," << returnValue.y_ << " | Distance to " << goalState.x_ << "," << goalState.y_ << " : " << distance << std::endl;//" | Length: " << length_ << std::endl;

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
