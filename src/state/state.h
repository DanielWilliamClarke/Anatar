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
	std::shared_ptr<State<T>> Yield();
	virtual void Update(float dt) = 0;
	virtual void Draw(std::shared_ptr<IRenderer> renderer, float interp) const = 0;

protected:
	virtual void Setup() = 0;
	virtual void TearDown() = 0;

	void Forward(T t);
	void Back();
	void SetBack(std::shared_ptr<State<T>> p);

private:
	void Transition(std::shared_ptr<State<T>> nextState);
	std::shared_ptr<State<T>> Pop(std::shared_ptr<State<T>> state);

private:
	std::unordered_map<T, std::shared_ptr<State<T>>> transtions;
	std::shared_ptr<State<T>> previous;
	std::shared_ptr<State<T>> next;
};

template <typename T>
std::shared_ptr<State<T>> State<T>::AddTransition(T t, std::shared_ptr<State<T>> state) {
	this->transtions[t] = state;
	return this->shared_from_this();
}

template <typename T>
std::shared_ptr<State<T>> State<T>::Yield() 
{
	if (this->next) {
		auto nextState = this->next;

		// Yield should be called before Update and Draw
		// So tearing down will occur cleanly between frames
		this->TearDown();
		this->previous = nullptr;
		this->next = nullptr;

		return nextState;
	}

	return this->shared_from_this();
}

template <typename T>
void State<T>::Forward(T t) {
	this->Transition(this->transtions.at(t));
}

template <typename T>
void State<T>::Back() {
	this->Transition(this->previous);
}

template <typename T>
void State<T>::SetBack(std::shared_ptr<State<T>> p) {
	this->previous = p;
}

template <typename T>
void State<T>::Transition(std::shared_ptr<State<T>> nextState)
{
	if (nextState)
	{
		// Prepare next state
		nextState->SetBack(this->shared_from_this());
		nextState->Setup();
		this->next = nextState;
	}
}

#endif // STATE