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

	private: System::Windows::Forms::RadioButton^ rbtn_MoveLight;
	public:

	private: System::Windows::Forms::RadioButton^ rbtn_ColorByPosition;

	public:

	private: System::Windows::Forms::RadioButton^ rbtn_MoveCubeToSphere;
	private: System::Windows::Forms::Button^ btn_ResetLightPosition;
	private: System::Windows::Forms::Button^ btn_ResetTeapotPosition;
	private: System::Windows::Forms::TrackBar^ trackBar_SpecularStrength;

	private: System::Windows::Forms::TrackBar^ trackBar_Red;

	private: System::Windows::Forms::TrackBar^ trackBar_Green;
	private: System::Windows::Forms::TrackBar^ trackBar_Blue;



	private: System::Windows::Forms::TextBox^ textBox_SpecularStrength;
	private: System::Windows::Forms::TextBox^ textBox_SpecularColor;
	private: System::Windows::Forms::TextBox^ textBox_R;
	private: System::Windows::Forms::TextBox^ textBox_G;
	private: System::Windows::Forms::TextBox^ textBox_B;

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
			this->rbtn_MoveLight = (gcnew System::Windows::Forms::RadioButton());
			this->rbtn_ColorByPosition = (gcnew System::Windows::Forms::RadioButton());
			this->rbtn_MoveCubeToSphere = (gcnew System::Windows::Forms::RadioButton());
			this->btn_ResetLightPosition = (gcnew System::Windows::Forms::Button());
			this->btn_ResetTeapotPosition = (gcnew System::Windows::Forms::Button());
			this->trackBar_SpecularStrength = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar_Red = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar_Green = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar_Blue = (gcnew System::Windows::Forms::TrackBar());
			this->textBox_SpecularStrength = (gcnew System::Windows::Forms::TextBox());
			this->textBox_SpecularColor = (gcnew System::Windows::Forms::TextBox());
			this->textBox_R = (gcnew System::Windows::Forms::TextBox());
			this->textBox_G = (gcnew System::Windows::Forms::TextBox());
			this->textBox_B = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_SpecularStrength))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_Red))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_Green))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_Blue))->BeginInit();
			this->SuspendLayout();
			// 
			// rbtn_MoveLight
			// 
			this->rbtn_MoveLight->AutoSize = true;
			this->rbtn_MoveLight->Location = System::Drawing::Point(13, 24);
			this->rbtn_MoveLight->Name = L"rbtn_MoveLight";
			this->rbtn_MoveLight->Size = System::Drawing::Size(78, 17);
			this->rbtn_MoveLight->TabIndex = 0;
			this->rbtn_MoveLight->TabStop = true;
			this->rbtn_MoveLight->Text = L"Move Light";
			this->rbtn_MoveLight->UseVisualStyleBackColor = true;
			this->rbtn_MoveLight->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::rbtn_MoveLight_CheckedChanged);
			// 
			// rbtn_ColorByPosition
			// 
			this->rbtn_ColorByPosition->AutoSize = true;
			this->rbtn_ColorByPosition->Location = System::Drawing::Point(13, 311);
			this->rbtn_ColorByPosition->Name = L"rbtn_ColorByPosition";
			this->rbtn_ColorByPosition->Size = System::Drawing::Size(104, 17);
			this->rbtn_ColorByPosition->TabIndex = 1;
			this->rbtn_ColorByPosition->TabStop = true;
			this->rbtn_ColorByPosition->Text = L"Color By Position";
			this->rbtn_ColorByPosition->UseVisualStyleBackColor = true;
			this->rbtn_ColorByPosition->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::rbtn_ColorByPosition_CheckedChanged);
			// 
			// rbtn_MoveCubeToSphere
			// 
			this->rbtn_MoveCubeToSphere->AutoSize = true;
			this->rbtn_MoveCubeToSphere->Location = System::Drawing::Point(13, 379);
			this->rbtn_MoveCubeToSphere->Name = L"rbtn_MoveCubeToSphere";
			this->rbtn_MoveCubeToSphere->Size = System::Drawing::Size(138, 17);
			this->rbtn_MoveCubeToSphere->TabIndex = 2;
			this->rbtn_MoveCubeToSphere->TabStop = true;
			this->rbtn_MoveCubeToSphere->Text = L"Move Cubes To Sphere";
			this->rbtn_MoveCubeToSphere->UseVisualStyleBackColor = true;
			this->rbtn_MoveCubeToSphere->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::rbtn_MoveCubeToSphere_CheckedChanged);
			// 
			// btn_ResetLightPosition
			// 
			this->btn_ResetLightPosition->Location = System::Drawing::Point(28, 48);
			this->btn_ResetLightPosition->Name = L"btn_ResetLightPosition";
			this->btn_ResetLightPosition->Size = System::Drawing::Size(123, 23);
			this->btn_ResetLightPosition->TabIndex = 3;
			this->btn_ResetLightPosition->Text = L"Reset Light Position";
			this->btn_ResetLightPosition->UseVisualStyleBackColor = true;
			this->btn_ResetLightPosition->Click += gcnew System::EventHandler(this, &ToolWindow::btn_ResetLightPosition_Click);
			// 
			// btn_ResetTeapotPosition
			// 
			this->btn_ResetTeapotPosition->Location = System::Drawing::Point(28, 335);
			this->btn_ResetTeapotPosition->Name = L"btn_ResetTeapotPosition";
			this->btn_ResetTeapotPosition->Size = System::Drawing::Size(123, 23);
			this->btn_ResetTeapotPosition->TabIndex = 4;
			this->btn_ResetTeapotPosition->Text = L"Reset Teapot Position";
			this->btn_ResetTeapotPosition->UseVisualStyleBackColor = true;
			this->btn_ResetTeapotPosition->Click += gcnew System::EventHandler(this, &ToolWindow::btn_ResetTeapotPosition_Click);
			// 
			// trackBar_SpecularStrength
			// 
			this->trackBar_SpecularStrength->AccessibleName = L"";
			this->trackBar_SpecularStrength->Location = System::Drawing::Point(125, 77);
			this->trackBar_SpecularStrength->Name = L"trackBar_SpecularStrength";
			this->trackBar_SpecularStrength->Size = System::Drawing::Size(284, 45);
			this->trackBar_SpecularStrength->TabIndex = 5;
			this->trackBar_SpecularStrength->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBar_SpecularStrength_Scroll);
			// 
			// trackBar_Red
			// 
			this->trackBar_Red->Location = System::Drawing::Point(125, 129);
			this->trackBar_Red->Name = L"trackBar_Red";
			this->trackBar_Red->Size = System::Drawing::Size(284, 45);
			this->trackBar_Red->TabIndex = 6;
			this->trackBar_Red->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBar_Red_Scroll);
			// 
			// trackBar_Green
			// 
			this->trackBar_Green->Location = System::Drawing::Point(125, 180);
			this->trackBar_Green->Name = L"trackBar_Green";
			this->trackBar_Green->Size = System::Drawing::Size(284, 45);
			this->trackBar_Green->TabIndex = 7;
			this->trackBar_Green->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBar_Green_Scroll);
			// 
			// trackBar_Blue
			// 
			this->trackBar_Blue->Location = System::Drawing::Point(125, 231);
			this->trackBar_Blue->Name = L"trackBar_Blue";
			this->trackBar_Blue->Size = System::Drawing::Size(284, 45);
			this->trackBar_Blue->TabIndex = 8;
			this->trackBar_Blue->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBar_Blue_Scroll);
			// 
			// textBox_SpecularStrength
			// 
			this->textBox_SpecularStrength->Location = System::Drawing::Point(28, 77);
			this->textBox_SpecularStrength->Name = L"textBox_SpecularStrength";
			this->textBox_SpecularStrength->Size = System::Drawing::Size(100, 20);
			this->textBox_SpecularStrength->TabIndex = 9;
			this->textBox_SpecularStrength->Text = L"Specular Strength";
			this->textBox_SpecularStrength->TextChanged += gcnew System::EventHandler(this, &ToolWindow::textBox1_TextChanged);
			// 
			// textBox_SpecularColor
			// 
			this->textBox_SpecularColor->Location = System::Drawing::Point(28, 128);
			this->textBox_SpecularColor->Name = L"textBox_SpecularColor";
			this->textBox_SpecularColor->Size = System::Drawing::Size(76, 20);
			this->textBox_SpecularColor->TabIndex = 10;
			this->textBox_SpecularColor->Text = L"Specular Color";
			// 
			// textBox_R
			// 
			this->textBox_R->BackColor = System::Drawing::Color::Red;
			this->textBox_R->Location = System::Drawing::Point(114, 128);
			this->textBox_R->Name = L"textBox_R";
			this->textBox_R->Size = System::Drawing::Size(14, 20);
			this->textBox_R->TabIndex = 12;
			this->textBox_R->Text = L"R";
			// 
			// textBox_G
			// 
			this->textBox_G->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->textBox_G->Location = System::Drawing::Point(114, 180);
			this->textBox_G->Name = L"textBox_G";
			this->textBox_G->Size = System::Drawing::Size(14, 20);
			this->textBox_G->TabIndex = 13;
			this->textBox_G->Text = L"G";
			// 
			// textBox_B
			// 
			this->textBox_B->BackColor = System::Drawing::Color::DeepSkyBlue;
			this->textBox_B->Location = System::Drawing::Point(114, 231);
			this->textBox_B->Name = L"textBox_B";
			this->textBox_B->Size = System::Drawing::Size(14, 20);
			this->textBox_B->TabIndex = 14;
			this->textBox_B->Text = L"B";
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(474, 442);
			this->Controls->Add(this->textBox_B);
			this->Controls->Add(this->textBox_G);
			this->Controls->Add(this->textBox_R);
			this->Controls->Add(this->textBox_SpecularColor);
			this->Controls->Add(this->textBox_SpecularStrength);
			this->Controls->Add(this->trackBar_Blue);
			this->Controls->Add(this->trackBar_Green);
			this->Controls->Add(this->trackBar_Red);
			this->Controls->Add(this->trackBar_SpecularStrength);
			this->Controls->Add(this->btn_ResetTeapotPosition);
			this->Controls->Add(this->btn_ResetLightPosition);
			this->Controls->Add(this->rbtn_MoveCubeToSphere);
			this->Controls->Add(this->rbtn_ColorByPosition);
			this->Controls->Add(this->rbtn_MoveLight);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"ToolWindow";
			this->Text = L"ToolWindow";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &ToolWindow::ToolWindow_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_SpecularStrength))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_Red))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_Green))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_Blue))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion Windows Form Designer generated code
	private: System::Void ToolWindow_Load(System::Object^ sender, System::EventArgs^ e) {
		rbtn_MoveLight->Checked = true;
	}


private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void rbtn_MoveLight_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void rbtn_ColorByPosition_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void rbtn_MoveCubeToSphere_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void btn_ResetTeapotPosition_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void btn_ResetLightPosition_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void trackBar_SpecularStrength_Scroll(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void trackBar_Red_Scroll(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void trackBar_Green_Scroll(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void trackBar_Blue_Scroll(System::Object^ sender, System::EventArgs^ e) {
}
};
}
