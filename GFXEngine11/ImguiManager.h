//Script to Initialize and Update the ImGui
#pragma once

class ImguiManager
{
public:
	ImguiManager();
	~ImguiManager();

	/// <summary>
	/// Start the Update of ImGui
	/// </summary>
	void Update();
	/// <summary>
	/// End the Update of ImGui
	/// </summary>
	void EndUpdate();
};

