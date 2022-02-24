//Script for a GameObject
#pragma once
#include <vector>
#include "Transform.h"
#include "Utils.h"

//Incomplete Class (No Circular Inclusion)
class Component;

class GameObject
{
public:
	GameObject(const char* _name)
	{
		//Set Name
		Name = _name;

		//initialize the Transform Component
		transform.Init();
	}

	//Transform Component of the GameObject
	Transform transform;

	/// <summary>
	/// Awake Function to Start all Components of the GameObject
	/// </summary>
	/// <param name="_p_d3ddevice"></param>
	/// <param name="_p_d3ddevicecontext"></param>
	/// <param name="_p_dt"></param>
	/// <returns></returns>
	INT Awake(ID3D11Device* _p_d3ddevice, ID3D11DeviceContext* _p_d3ddevicecontext, FLOAT* _p_dt);
	/// <summary>
	/// Start all Components of the GameObject
	/// </summary>
	void Start();
	/// <summary>
	/// Update all Components of the GameObjects
	/// </summary>
	void Update();
	/// <summary>
	/// Deinit all Components
	/// </summary>
	void DeInit();

	/// <summary>
	/// Get the First Component of the given Type
	/// </summary>
	/// <typeparam name="T">Component Type</typeparam>
	/// <returns>Return the First Component Type of the given Type</returns>
	template<typename T>
	T* GetComponent();

	/// <summary>
	/// Add a new Component to the Component List
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns>Returns the Added Component</returns>
	template<typename T>
	T* AddComponent();

	bool IsActive = true;

	//UI Name of the GameObject
	const char* Name;

private:
	//List of All Components
	std::vector<Component*> allComponents;
};

// --> Have to be in the Header <--

template<typename T>
T* GameObject::GetComponent()
{
	for (Component* c : allComponents)
	{
		//Check if can Convert the Component to the given type
		if (dynamic_cast<T*>(c) != nullptr)
		{
			//Return Component of the Type
			return (T*)c;
		}
	}

	return nullptr;
}

template<typename T>
T* GameObject::AddComponent()
{
	// Add a new Component of the Given type
	T* component = new T(this);
	allComponents.push_back(component);
	//Return the Component as the Given type
	return (T*)component;

	return nullptr;
}


