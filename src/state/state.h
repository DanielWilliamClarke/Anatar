#ifndef STATE
#define STATE
#pragma once

#include <memory>
#include <stack>
#include <unordered_map>

class IRenderer;

template <typename T>
class State: public std::enable_shared_from_this<State<T>> {
public:
	State() = default;
	virtual ~State() = default;

	std::shared_ptr<State<T>> AddTransition(T t, std::shared_ptr<State<T>> state);
	virtual std::shared_ptr<State<T>> Update(float dt) = 0;
	virtual void Draw(std::shared_ptr<IRenderer> renderer, float interp) const = 0;

protected:
	std::shared_ptr<State<T>> Transition(T t) const;
	std::shared_ptr<State<T>> Backtrack() const;
	std::shared_ptr<State<T>> SetBacktrack(std::shared_ptr<State<T>> p);

private:
	std::unordered_map<T, std::shared_ptr<State<T>>> transtions;
	std::shared_ptr<State<T>> previous;
};

template <typename T>
std::shared_ptr<State<T>> State<T>::AddTransition(T t, std::shared_ptr<State<T>> state) {
	this->transtions.insert(t, state);
	return this->shared_from_this();
}

template <typename T>
std::shared_ptr<State<T>> State<T>::Transition(T t) const {
	return this->transtions.at(t)->SetBacktrack(this->shared_from_this());
}

template <typename T>
std::shared_ptr<State<T>> State<T>::SetBacktrack(std::shared_ptr<State<T>> p) {
	this->previous = p;
	return this->shared_from_this();
}

template <typename T>
std::shared_ptr<State<T>> State<T>::Backtrack() const {
	return this->previous;
}

#endif // STATE