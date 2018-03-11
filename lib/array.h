//
//  lib/array.h
//  lets
//
//  Created by Dragan Stepan on 11.03.18.
//  Copyright © 2018 umbokc. All rights reserved.
//

#ifndef lib__array_h
#define lib__array_h

#include <algorithm>

namespace lets_lib{
	template<typename T>
	class Array{
	private:
		size_t size_;

		T *data = new T[0];
	public:


		Array(){
			this->size_ = 0;
			this->data = nullptr;
		}

		Array(size_t n){
			this->size_ = n;
			this->data = new T[n];
		}

		Array(std::initializer_list<T> init){
			this->size_ = init.size();
			this->data = new T[this->size_];
			size_t index = 0;
			for(const T& i: init){
				this->set(index, i);
				index++;
			}
		}

		bool has(const T& val) const {
			return this->find(val) != this->size();
		}

		size_t find(const T& val) const {

			size_t i = 0;

			T *first = this->data;
			T *last = this->data + this->size();

			while (first != last and *first != val){
				++first, ++i;
			}

			return i;
		}

		void set(const size_t& index, const T& val){

			if(index >= this->size())
				incr_resize(index);

			this->data[index] = val;
		}

		T& at(const size_t& index){

			if(index >= this->size())
				incr_resize(index);

			return this->data[index];
		}

		T& operator[] (const size_t& index){
			return this->at(index);
		}

		const T& operator[] (const size_t& index) const {
			return this->at(index);
		}

		const size_t size() const{
			return this->size_;
		}

	private:
		void incr_resize(){
			T *new_data = new T[this->size()+1];
			std::copy(this->data, this->data + this->size(), new_data);
			this->data = new_data;
			this->size_++;
			delete[] new_data;
		}

		void incr_resize(const size_t& new_size_){
			size_t new_size = new_size_ + 1;
			T *new_data = new T[new_size];
			std::copy(this->data, this->data + this->size(), new_data);
			this->data = new_data;
			this->size_ = new_size;
			delete[] new_data;
		}
	};
}

#endif /* lib__array_h */

