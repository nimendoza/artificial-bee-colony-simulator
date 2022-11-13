#pragma once
#include "pch.h"
class Base {
public:
	Base() {}
	Base(const Base& rhs) = delete;
	Base(Base&& rhs) = delete;
	~Base() = default;
	Base& operator =(const Base& rhs) = delete;
	Base& operator =(Base&& rhs) = delete;

	virtual void update(const double& time) {}
	virtual void render(Window& window) {}
};