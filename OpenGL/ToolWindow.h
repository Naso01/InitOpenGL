#pragma once
#include "GameController.h"

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

	private: System::Windows::Forms::RadioButton^ rbtn_MoveLight;

	private: System::Windows::Forms::RadioButton^ rbtn_ColorByPosition;

	private: System::Windows::Forms::RadioButton^ rbtn_MoveCubeToSphere;
	private: System::Windows::Forms::Button^ btn_ResetLightPosition;
	private: System::Windows::Forms::Button^ btn_ResetTeapotPosition;
	private: System::Windows::Forms::TrackBar^ trackBar_SpecularStrength;

	private: System::Windows::Forms::TrackBar^ trackBar_Red;

	private: System::Windows::Forms::TrackBar^ trackBar_Green;
	private: System::Windows::Forms::TrackBar^ trackBar_Blue;


	private: System::Windows::Forms::TextBox^ textBox_R;
	private: System::Windows::Forms::TextBox^ textBox_G;
	private: System::Windows::Forms::TextBox^ textBox_B;

	private: System::Windows::Forms::Label^ lbl_SpecularStrength;
	private: System::Windows::Forms::Label^ lbl_SpecularColor;

	private: System::Windows::Forms::Label^ lbl_RedValue;
	private: System::Windows::Forms::Label^ lbl_SpecStrValue;
	private: System::Windows::Forms::Label^ lbl_GreenValue;
	private: System::Windows::Forms::Label^ lbl_BlueValue;

	public:

//Members
		static unsigned short SpecularStrength;
		
		static float RenderRedChannel;
		static float RenderGreenChannel;
		static float RenderBlueChannel;

		ToolWindow(void)
		{
			InitializeComponent();
			SpecularStrength = trackBar_SpecularStrength->Value;
			lbl_RedValue->Text = (trackBar_Red->Value / 100).ToString("F2");
			lbl_GreenValue->Text = (trackBar_Green->Value / 100).ToString("F2");
			lbl_BlueValue->Text = (trackBar_Blue->Value / 100).ToString("F2");

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
			this->textBox_R = (gcnew System::Windows::Forms::TextBox());
			this->textBox_G = (gcnew System::Windows::Forms::TextBox());
			this->textBox_B = (gcnew System::Windows::Forms::TextBox());
			this->lbl_SpecularStrength = (gcnew System::Windows::Forms::Label());
			this->lbl_SpecularColor = (gcnew System::Windows::Forms::Label());
			this->lbl_RedValue = (gcnew System::Windows::Forms::Label());
			this->lbl_SpecStrValue = (gcnew System::Windows::Forms::Label());
			this->lbl_GreenValue = (gcnew System::Windows::Forms::Label());
			this->lbl_BlueValue = (gcnew System::Windows::Forms::Label());
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
			this->trackBar_SpecularStrength->Maximum = 128;
			this->trackBar_SpecularStrength->Minimum = 1;
			this->trackBar_SpecularStrength->Name = L"trackBar_SpecularStrength";
			this->trackBar_SpecularStrength->Size = System::Drawing::Size(284, 45);
			this->trackBar_SpecularStrength->TabIndex = 5;
			this->trackBar_SpecularStrength->Value = 4;
			this->trackBar_SpecularStrength->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBar_SpecularStrength_Scroll);
			// 
			// trackBar_Red
			// 
			this->trackBar_Red->Location = System::Drawing::Point(125, 129);
			this->trackBar_Red->Maximum = 300;
			this->trackBar_Red->Name = L"trackBar_Red";
			this->trackBar_Red->Size = System::Drawing::Size(284, 45);
			this->trackBar_Red->TabIndex = 6;
			this->trackBar_Red->Value = 100;
			this->trackBar_Red->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBar_Red_Scroll);
			// 
			// trackBar_Green
			// 
			this->trackBar_Green->Location = System::Drawing::Point(125, 180);
			this->trackBar_Green->Maximum = 300;
			this->trackBar_Green->Name = L"trackBar_Green";
			this->trackBar_Green->Size = System::Drawing::Size(284, 45);
			this->trackBar_Green->TabIndex = 7;
			this->trackBar_Green->Value = 100;
			this->trackBar_Green->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBar_Green_Scroll);
			// 
			// trackBar_Blue
			// 
			this->trackBar_Blue->Location = System::Drawing::Point(125, 231);
			this->trackBar_Blue->Maximum = 300;
			this->trackBar_Blue->Name = L"trackBar_Blue";
			this->trackBar_Blue->Size = System::Drawing::Size(284, 45);
			this->trackBar_Blue->TabIndex = 8;
			this->trackBar_Blue->Value = 100;
			this->trackBar_Blue->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBar_Blue_Scroll);
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
			// lbl_SpecularStrength
			// 
			this->lbl_SpecularStrength->AutoSize = true;
			this->lbl_SpecularStrength->Location = System::Drawing::Point(27, 77);
			this->lbl_SpecularStrength->Name = L"lbl_SpecularStrength";
			this->lbl_SpecularStrength->Size = System::Drawing::Size(92, 13);
			this->lbl_SpecularStrength->TabIndex = 15;
			this->lbl_SpecularStrength->Text = L"Specular Strength";
			// 
			// lbl_SpecularColor
			// 
			this->lbl_SpecularColor->AutoSize = true;
			this->lbl_SpecularColor->Location = System::Drawing::Point(27, 128);
			this->lbl_SpecularColor->Name = L"lbl_SpecularColor";
			this->lbl_SpecularColor->Size = System::Drawing::Size(76, 13);
			this->lbl_SpecularColor->TabIndex = 16;
			this->lbl_SpecularColor->Text = L"Specular Color";
			// 
			// lbl_RedValue
			// 
			this->lbl_RedValue->AutoSize = true;
			this->lbl_RedValue->Location = System::Drawing::Point(405, 135);
			this->lbl_RedValue->Name = L"lbl_RedValue";
			this->lbl_RedValue->Size = System::Drawing::Size(0, 13);
			this->lbl_RedValue->TabIndex = 18;
			// 
			// lbl_SpecStrValue
			// 
			this->lbl_SpecStrValue->AutoSize = true;
			this->lbl_SpecStrValue->Location = System::Drawing::Point(405, 77);
			this->lbl_SpecStrValue->Name = L"lbl_SpecStrValue";
			this->lbl_SpecStrValue->Size = System::Drawing::Size(0, 13);
			this->lbl_SpecStrValue->TabIndex = 19;
			// 
			// lbl_GreenValue
			// 
			this->lbl_GreenValue->AutoSize = true;
			this->lbl_GreenValue->Location = System::Drawing::Point(405, 183);
			this->lbl_GreenValue->Name = L"lbl_GreenValue";
			this->lbl_GreenValue->Size = System::Drawing::Size(0, 13);
			this->lbl_GreenValue->TabIndex = 20;
			// 
			// lbl_BlueValue
			// 
			this->lbl_BlueValue->AutoSize = true;
			this->lbl_BlueValue->Location = System::Drawing::Point(405, 234);
			this->lbl_BlueValue->Name = L"lbl_BlueValue";
			this->lbl_BlueValue->Size = System::Drawing::Size(0, 13);
			this->lbl_BlueValue->TabIndex = 21;
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(474, 442);
			this->Controls->Add(this->lbl_BlueValue);
			this->Controls->Add(this->lbl_GreenValue);
			this->Controls->Add(this->lbl_SpecStrValue);
			this->Controls->Add(this->lbl_RedValue);
			this->Controls->Add(this->lbl_SpecularColor);
			this->Controls->Add(this->lbl_SpecularStrength);
			this->Controls->Add(this->textBox_B);
			this->Controls->Add(this->textBox_G);
			this->Controls->Add(this->textBox_R);
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

		trackBar_Red->Minimum = 0;
		trackBar_Red->Maximum = 300;
		trackBar_Red->Value = 128;

		trackBar_Green->Minimum = 0;
		trackBar_Green->Maximum = 300;
		trackBar_Green->Value = 128;

		trackBar_Blue->Minimum = 0;
		trackBar_Blue->Maximum = 300;
		trackBar_Blue->Value = 128;

		trackBar_SpecularStrength->Minimum = 0;
		trackBar_SpecularStrength->Maximum = 128;
		trackBar_SpecularStrength->Value = 32;
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
			GameController::SetLightPosition({ 0.0f, 0.0f, 0.1f });

		}

		//TrackBars
		private: System::Void trackBar_SpecularStrength_Scroll(System::Object^ sender, System::EventArgs^ e) {
			unsigned short specStrValue = trackBar_SpecularStrength->Value;
			SpecularStrength = specStrValue;
			lbl_SpecStrValue->Text = specStrValue.ToString();
		}
		private: System::Void trackBar_Red_Scroll(System::Object^ sender, System::EventArgs^ e) {
			float redValue = trackBar_Red->Value / 100.0f;
			RenderRedChannel = redValue;
			lbl_RedValue->Text = redValue.ToString("F2");
		}
		private: System::Void trackBar_Green_Scroll(System::Object^ sender, System::EventArgs^ e) {
			float greenValue = trackBar_Green->Value / 100.0f;
			RenderGreenChannel = greenValue;
			lbl_GreenValue->Text = greenValue.ToString("F2");
		}
		private: System::Void trackBar_Blue_Scroll(System::Object^ sender, System::EventArgs^ e) {
			float blueValue = trackBar_Blue->Value / 100.0f;
			RenderBlueChannel = blueValue;
			lbl_BlueValue->Text = blueValue.ToString("F2");
		}

};
}
