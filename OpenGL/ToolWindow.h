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

	private: System::Windows::Forms::RadioButton^ rbtn_MoveLight;

	private: System::Windows::Forms::Button^ btn_ResetLightPosition;

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

	private: System::Windows::Forms::RadioButton^ rbtn_transform;

	private: System::Windows::Forms::RadioButton^ rbtn_spacescene;
	private: System::Windows::Forms::Button^ btn_resettransform;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;
	private: System::Windows::Forms::Label^ lbl_frequency;
	private: System::Windows::Forms::Label^ lbl_amplitude;
	private: System::Windows::Forms::CheckBox^ box_translate;
	private: System::Windows::Forms::CheckBox^ box_rotate;
	private: System::Windows::Forms::CheckBox^ box_scale;
	private: System::Windows::Forms::TrackBar^ trackBar_Frequency;
	private: System::Windows::Forms::TrackBar^ trackBar_Amplitude;
	private: System::Windows::Forms::Label^ lbl_frequencyvalue;
	private: System::Windows::Forms::Label^ lbl_amplitudevalue;
	private: System::Windows::Forms::CheckBox^ box_wireframe;
	private: System::Windows::Forms::CheckBox^ box_tintblue;


	private: System::Windows::Forms::RadioButton^ rbtn_waterscene;
	public:
		//---------------- Static Variables ------------------------------------------------------------------------
		//Light Settings
		static unsigned short SpecularStrength;
		static float RenderRedChannel;
		static float RenderGreenChannel;
		static float RenderBlueChannel;
		static bool MoveLight;
		static bool ResetLightPosition;
		//Transform
		static bool ResetTransform;
		static bool TransformEnabled;
		static bool TranslateEnabled;
		static bool RotateEnabled;
		static bool ScaleEnabled;
		//Water Scene
		static bool WaterSceneEnabled;
		static bool WireframeEnabled;
		static bool TintBlueEnabled;
		static float Frequency;
		static float Amplitude;

		ToolWindow(void)
		{
			InitializeComponent();
			unsigned short specStrValue = trackBar_SpecularStrength->Value; //Specular Strength
			SpecularStrength = specStrValue;
			lbl_SpecStrValue->Text = specStrValue.ToString();

			float redValue = trackBar_Red->Value / 100.0f; //Red
			RenderRedChannel = redValue;
			lbl_RedValue->Text = redValue.ToString("F2");

			float greenValue = trackBar_Green->Value / 100.0f; //Green
			RenderGreenChannel = greenValue;
			lbl_GreenValue->Text = greenValue.ToString("F2");

			float blueValue = trackBar_Blue->Value / 100.0f; //Blue
			RenderBlueChannel = blueValue;
			lbl_BlueValue->Text = blueValue.ToString("F2");
			
			ResetLightPosition = false;

			MoveLight = rbtn_MoveLight->Checked;


			TransformEnabled = rbtn_transform->Checked;
			ResetTransform = false;
			TranslateEnabled = box_translate->Checked;
			RotateEnabled = box_rotate->Checked;
			ScaleEnabled = box_scale->Checked;

			WaterSceneEnabled = rbtn_waterscene->Checked;
			WireframeEnabled = box_wireframe->Checked;
			TintBlueEnabled = box_tintblue->Checked;
			Frequency = trackBar_Frequency->Value / 100.0f;
			lbl_frequencyvalue->Text = Frequency.ToString("F2");
			Amplitude = trackBar_Amplitude->Value / 100.0f;
			lbl_amplitudevalue->Text = Amplitude.ToString("F2");
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
			this->btn_ResetLightPosition = (gcnew System::Windows::Forms::Button());
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
			this->rbtn_transform = (gcnew System::Windows::Forms::RadioButton());
			this->rbtn_spacescene = (gcnew System::Windows::Forms::RadioButton());
			this->btn_resettransform = (gcnew System::Windows::Forms::Button());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->lbl_frequency = (gcnew System::Windows::Forms::Label());
			this->lbl_amplitude = (gcnew System::Windows::Forms::Label());
			this->box_translate = (gcnew System::Windows::Forms::CheckBox());
			this->box_rotate = (gcnew System::Windows::Forms::CheckBox());
			this->box_scale = (gcnew System::Windows::Forms::CheckBox());
			this->trackBar_Frequency = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar_Amplitude = (gcnew System::Windows::Forms::TrackBar());
			this->lbl_frequencyvalue = (gcnew System::Windows::Forms::Label());
			this->lbl_amplitudevalue = (gcnew System::Windows::Forms::Label());
			this->box_wireframe = (gcnew System::Windows::Forms::CheckBox());
			this->box_tintblue = (gcnew System::Windows::Forms::CheckBox());
			this->rbtn_waterscene = (gcnew System::Windows::Forms::RadioButton());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_SpecularStrength))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_Red))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_Green))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_Blue))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_Frequency))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_Amplitude))->BeginInit();
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
			// rbtn_transform
			// 
			this->rbtn_transform->AutoSize = true;
			this->rbtn_transform->Location = System::Drawing::Point(13, 324);
			this->rbtn_transform->Name = L"rbtn_transform";
			this->rbtn_transform->Size = System::Drawing::Size(72, 17);
			this->rbtn_transform->TabIndex = 22;
			this->rbtn_transform->TabStop = true;
			this->rbtn_transform->Text = L"Transform";
			this->rbtn_transform->UseVisualStyleBackColor = true;
			this->rbtn_transform->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::rbtn_transform_CheckedChanged);
			// 
			// rbtn_spacescene
			// 
			this->rbtn_spacescene->AutoSize = true;
			this->rbtn_spacescene->Location = System::Drawing::Point(13, 697);
			this->rbtn_spacescene->Name = L"rbtn_spacescene";
			this->rbtn_spacescene->Size = System::Drawing::Size(90, 17);
			this->rbtn_spacescene->TabIndex = 24;
			this->rbtn_spacescene->TabStop = true;
			this->rbtn_spacescene->Text = L"Space Scene";
			this->rbtn_spacescene->UseVisualStyleBackColor = true;
			this->rbtn_spacescene->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::rbtn_spacescene_CheckedChanged);
			// 
			// btn_resettransform
			// 
			this->btn_resettransform->Location = System::Drawing::Point(30, 357);
			this->btn_resettransform->Name = L"btn_resettransform";
			this->btn_resettransform->Size = System::Drawing::Size(123, 23);
			this->btn_resettransform->TabIndex = 25;
			this->btn_resettransform->Text = L"Reset Transform";
			this->btn_resettransform->UseVisualStyleBackColor = true;
			this->btn_resettransform->Click += gcnew System::EventHandler(this, &ToolWindow::btn_resettransform_Click);
			// 
			// lbl_frequency
			// 
			this->lbl_frequency->AutoSize = true;
			this->lbl_frequency->Location = System::Drawing::Point(34, 554);
			this->lbl_frequency->Name = L"lbl_frequency";
			this->lbl_frequency->Size = System::Drawing::Size(57, 13);
			this->lbl_frequency->TabIndex = 26;
			this->lbl_frequency->Text = L"Frequency";
			// 
			// lbl_amplitude
			// 
			this->lbl_amplitude->AutoSize = true;
			this->lbl_amplitude->Location = System::Drawing::Point(38, 605);
			this->lbl_amplitude->Name = L"lbl_amplitude";
			this->lbl_amplitude->Size = System::Drawing::Size(53, 13);
			this->lbl_amplitude->TabIndex = 27;
			this->lbl_amplitude->Text = L"Amplitude";
			// 
			// box_translate
			// 
			this->box_translate->AutoSize = true;
			this->box_translate->Location = System::Drawing::Point(48, 386);
			this->box_translate->Name = L"box_translate";
			this->box_translate->Size = System::Drawing::Size(70, 17);
			this->box_translate->TabIndex = 28;
			this->box_translate->Text = L"Translate";
			this->box_translate->UseVisualStyleBackColor = true;
			this->box_translate->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::box_translate_CheckedChanged);
			// 
			// box_rotate
			// 
			this->box_rotate->AutoSize = true;
			this->box_rotate->Location = System::Drawing::Point(48, 409);
			this->box_rotate->Name = L"box_rotate";
			this->box_rotate->Size = System::Drawing::Size(58, 17);
			this->box_rotate->TabIndex = 29;
			this->box_rotate->Text = L"Rotate";
			this->box_rotate->UseVisualStyleBackColor = true;
			this->box_rotate->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::box_rotate_CheckedChanged);
			// 
			// box_scale
			// 
			this->box_scale->AutoSize = true;
			this->box_scale->Location = System::Drawing::Point(48, 432);
			this->box_scale->Name = L"box_scale";
			this->box_scale->Size = System::Drawing::Size(53, 17);
			this->box_scale->TabIndex = 30;
			this->box_scale->Text = L"Scale";
			this->box_scale->UseVisualStyleBackColor = true;
			this->box_scale->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::box_scale_CheckedChanged);
			// 
			// trackBar_Frequency
			// 
			this->trackBar_Frequency->Location = System::Drawing::Point(97, 554);
			this->trackBar_Frequency->Maximum = 400;
			this->trackBar_Frequency->Name = L"trackBar_Frequency";
			this->trackBar_Frequency->Size = System::Drawing::Size(284, 45);
			this->trackBar_Frequency->TabIndex = 31;
			this->trackBar_Frequency->Value = 100;
			this->trackBar_Frequency->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBar_Frequency_Scroll);
			// 
			// trackBar_Amplitude
			// 
			this->trackBar_Amplitude->Location = System::Drawing::Point(97, 605);
			this->trackBar_Amplitude->Maximum = 100;
			this->trackBar_Amplitude->Name = L"trackBar_Amplitude";
			this->trackBar_Amplitude->Size = System::Drawing::Size(284, 45);
			this->trackBar_Amplitude->TabIndex = 32;
			this->trackBar_Amplitude->Value = 1;
			this->trackBar_Amplitude->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBar_Amplitude_Scroll);
			// 
			// lbl_frequencyvalue
			// 
			this->lbl_frequencyvalue->AutoSize = true;
			this->lbl_frequencyvalue->Location = System::Drawing::Point(381, 554);
			this->lbl_frequencyvalue->Name = L"lbl_frequencyvalue";
			this->lbl_frequencyvalue->Size = System::Drawing::Size(0, 13);
			this->lbl_frequencyvalue->TabIndex = 33;
			// 
			// lbl_amplitudevalue
			// 
			this->lbl_amplitudevalue->AutoSize = true;
			this->lbl_amplitudevalue->Location = System::Drawing::Point(381, 605);
			this->lbl_amplitudevalue->Name = L"lbl_amplitudevalue";
			this->lbl_amplitudevalue->Size = System::Drawing::Size(0, 13);
			this->lbl_amplitudevalue->TabIndex = 34;
			// 
			// box_wireframe
			// 
			this->box_wireframe->AutoSize = true;
			this->box_wireframe->Location = System::Drawing::Point(37, 656);
			this->box_wireframe->Name = L"box_wireframe";
			this->box_wireframe->Size = System::Drawing::Size(112, 17);
			this->box_wireframe->TabIndex = 36;
			this->box_wireframe->Text = L"Wireframe Render";
			this->box_wireframe->UseVisualStyleBackColor = true;
			this->box_wireframe->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::box_wireframe_CheckedChanged);
			// 
			// box_tintblue
			// 
			this->box_tintblue->AutoSize = true;
			this->box_tintblue->Location = System::Drawing::Point(37, 679);
			this->box_tintblue->Name = L"box_tintblue";
			this->box_tintblue->Size = System::Drawing::Size(68, 17);
			this->box_tintblue->TabIndex = 37;
			this->box_tintblue->Text = L"Tint Blue";
			this->box_tintblue->UseVisualStyleBackColor = true;
			this->box_tintblue->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::box_tintblue_CheckedChanged);
			// 
			// rbtn_waterscene
			// 
			this->rbtn_waterscene->AutoSize = true;
			this->rbtn_waterscene->Location = System::Drawing::Point(13, 531);
			this->rbtn_waterscene->Name = L"rbtn_waterscene";
			this->rbtn_waterscene->Size = System::Drawing::Size(88, 17);
			this->rbtn_waterscene->TabIndex = 40;
			this->rbtn_waterscene->TabStop = true;
			this->rbtn_waterscene->Text = L"Water Scene";
			this->rbtn_waterscene->UseVisualStyleBackColor = true;
			this->rbtn_waterscene->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::rbtn_waterscene_CheckedChanged);
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(522, 726);
			this->Controls->Add(this->rbtn_waterscene);
			this->Controls->Add(this->box_tintblue);
			this->Controls->Add(this->box_wireframe);
			this->Controls->Add(this->lbl_amplitudevalue);
			this->Controls->Add(this->lbl_frequencyvalue);
			this->Controls->Add(this->trackBar_Amplitude);
			this->Controls->Add(this->trackBar_Frequency);
			this->Controls->Add(this->box_scale);
			this->Controls->Add(this->box_rotate);
			this->Controls->Add(this->box_translate);
			this->Controls->Add(this->lbl_amplitude);
			this->Controls->Add(this->lbl_frequency);
			this->Controls->Add(this->btn_resettransform);
			this->Controls->Add(this->rbtn_spacescene);
			this->Controls->Add(this->rbtn_transform);
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
			this->Controls->Add(this->btn_ResetLightPosition);
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_Frequency))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar_Amplitude))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion Windows Form Designer generated code

	private: System::Void ToolWindow_Load(System::Object^ sender, System::EventArgs^ e) {
	}
#pragma region Light
	private: System::Void rbtn_MoveLight_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		MoveLight = rbtn_MoveLight->Checked;
	}
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
	private: System::Void btn_ResetLightPosition_Click(System::Object^ sender, System::EventArgs^ e) {	
		ResetLightPosition = true;
	}
	

#pragma endregion Light
#pragma region Transform
private: System::Void rbtn_transform_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	TransformEnabled = rbtn_transform->Checked;
	ResetTransform = true;
}
private: System::Void btn_resettransform_Click(System::Object^ sender, System::EventArgs^ e) {
	ResetTransform = true;
}
private: System::Void box_translate_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	TranslateEnabled = box_translate->Checked;
}
private: System::Void box_rotate_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	RotateEnabled = box_rotate->Checked;
}
private: System::Void box_scale_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	ScaleEnabled = box_scale->Checked;
}
#pragma endregion Transform

#pragma region Water Scene
private: System::Void rbtn_waterscene_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	WaterSceneEnabled = rbtn_waterscene->Checked;
}
private: System::Void trackBar_Frequency_Scroll(System::Object^ sender, System::EventArgs^ e) {
	Frequency = trackBar_Frequency->Value / 100.0f;
	lbl_frequencyvalue->Text = Frequency.ToString("F2");
}
private: System::Void trackBar_Amplitude_Scroll(System::Object^ sender, System::EventArgs^ e) {
	Amplitude = trackBar_Amplitude->Value / 100.0f;
	lbl_amplitudevalue->Text = Amplitude.ToString("F2");
}
private: System::Void box_wireframe_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	WireframeEnabled = box_wireframe->Checked;
}
private: System::Void box_tintblue_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	TintBlueEnabled = box_tintblue->Checked;
}

#pragma endregion Water Scene
	   //Space Scene
private: System::Void rbtn_spacescene_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}

};
}
