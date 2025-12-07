#pragma once

namespace OpenGL {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ToolWindow
	/// </summary>
	public ref class ToolWindow : public System::Windows::Forms::Form
	{
	public:
		static bool RenderRedChannel;
		static bool RenderGreenChannel;
	private: System::Windows::Forms::RadioButton^ rdb_movelight;
	public:
	private: System::Windows::Forms::RadioButton^ rdb_transformation;
	private: System::Windows::Forms::RadioButton^ rtb_waterscene;

	private: System::Windows::Forms::Button^ btn_resetlightposition;

		   static bool RenderBlueChannel;

		ToolWindow(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ToolWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>




#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->rdb_movelight = (gcnew System::Windows::Forms::RadioButton());
			this->rdb_transformation = (gcnew System::Windows::Forms::RadioButton());
			this->rtb_waterscene = (gcnew System::Windows::Forms::RadioButton());
			this->btn_resetlightposition = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// rdb_movelight
			// 
			this->rdb_movelight->AutoSize = true;
			this->rdb_movelight->Location = System::Drawing::Point(12, 12);
			this->rdb_movelight->Name = L"rdb_movelight";
			this->rdb_movelight->Size = System::Drawing::Size(78, 17);
			this->rdb_movelight->TabIndex = 0;
			this->rdb_movelight->TabStop = true;
			this->rdb_movelight->Text = L"Move Light";
			this->rdb_movelight->UseVisualStyleBackColor = true;
			// 
			// rdb_transformation
			// 
			this->rdb_transformation->AutoSize = true;
			this->rdb_transformation->Location = System::Drawing::Point(12, 294);
			this->rdb_transformation->Name = L"rdb_transformation";
			this->rdb_transformation->Size = System::Drawing::Size(95, 17);
			this->rdb_transformation->TabIndex = 1;
			this->rdb_transformation->TabStop = true;
			this->rdb_transformation->Text = L"Transformation";
			this->rdb_transformation->UseVisualStyleBackColor = true;
			// 
			// rtb_waterscene
			// 
			this->rtb_waterscene->AutoSize = true;
			this->rtb_waterscene->Location = System::Drawing::Point(19, 476);
			this->rtb_waterscene->Name = L"rtb_waterscene";
			this->rtb_waterscene->Size = System::Drawing::Size(88, 17);
			this->rtb_waterscene->TabIndex = 2;
			this->rtb_waterscene->TabStop = true;
			this->rtb_waterscene->Text = L"Water Scene";
			this->rtb_waterscene->UseVisualStyleBackColor = true;
			// 
			// btn_resetlightposition
			// 
			this->btn_resetlightposition->Location = System::Drawing::Point(12, 35);
			this->btn_resetlightposition->Name = L"btn_resetlightposition";
			this->btn_resetlightposition->Size = System::Drawing::Size(133, 29);
			this->btn_resetlightposition->TabIndex = 4;
			this->btn_resetlightposition->Text = L"Reset Light Position";
			this->btn_resetlightposition->UseVisualStyleBackColor = true;
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(599, 650);
			this->Controls->Add(this->btn_resetlightposition);
			this->Controls->Add(this->rtb_waterscene);
			this->Controls->Add(this->rdb_transformation);
			this->Controls->Add(this->rdb_movelight);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"ToolWindow";
			this->Text = L"ToolWindow";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &ToolWindow::ToolWindow_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ToolWindow_Load(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
