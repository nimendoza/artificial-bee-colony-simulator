#pragma once
class Base {
public:
	Base() {}
	Base(Base&& rhs) = delete;
	Base(const Base& rhs) = delete;
	Base& operator =(Base&& rhs) = delete;
	Base& operator =(const Base& rhs) = delete;
	~Base() = default;

	virtual void update(const double& time) {}
	virtual void render(Plane& window) {}
};