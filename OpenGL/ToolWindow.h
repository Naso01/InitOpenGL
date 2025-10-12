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

		static float YScale;
		static float UScale;
		static float VScale;

		ToolWindow(void)
		{
			InitializeComponent();
			YScale = 100;
			UScale = 100;
			VScale = 100;
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
	private: System::Windows::Forms::TrackBar^ trackBarY;
	private: System::Windows::Forms::TrackBar^ trackBarU;
	private: System::Windows::Forms::TrackBar^ trackBarV;
	private: System::Windows::Forms::Label^ labelY;
	private: System::Windows::Forms::Label^ labelU;
	private: System::Windows::Forms::Label^ labelV;
	private: System::Windows::Forms::CheckBox^ checkBoxInvert;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->trackBarY = (gcnew System::Windows::Forms::TrackBar());
			this->trackBarU = (gcnew System::Windows::Forms::TrackBar());
			this->trackBarV = (gcnew System::Windows::Forms::TrackBar());
			this->labelY = (gcnew System::Windows::Forms::Label());
			this->labelU = (gcnew System::Windows::Forms::Label());
			this->labelV = (gcnew System::Windows::Forms::Label());
			this->checkBoxInvert = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarY))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarU))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarV))->BeginInit();
			this->SuspendLayout();
			// 
			// trackBarY
			// 
			this->trackBarY->Location = System::Drawing::Point(20, 20);
			this->trackBarY->Maximum = 200;
			this->trackBarY->Name = L"trackBarY";
			this->trackBarY->Size = System::Drawing::Size(200, 45);
			this->trackBarY->TabIndex = 0;
			this->trackBarY->TickFrequency = 10;
			this->trackBarY->Value = 100;
			this->trackBarY->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBarY_Scroll);
			// 
			// trackBarU
			// 
			this->trackBarU->Location = System::Drawing::Point(20, 60);
			this->trackBarU->Maximum = 200;
			this->trackBarU->Name = L"trackBarU";
			this->trackBarU->Size = System::Drawing::Size(200, 45);
			this->trackBarU->TabIndex = 2;
			this->trackBarU->TickFrequency = 10;
			this->trackBarU->Value = 100;
			this->trackBarU->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBarU_Scroll);
			// 
			// trackBarV
			// 
			this->trackBarV->Location = System::Drawing::Point(20, 100);
			this->trackBarV->Maximum = 200;
			this->trackBarV->Name = L"trackBarV";
			this->trackBarV->Size = System::Drawing::Size(200, 45);
			this->trackBarV->TabIndex = 4;
			this->trackBarV->TickFrequency = 10;
			this->trackBarV->Value = 100;
			this->trackBarV->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBarV_Scroll);
			// 
			// labelY
			// 
			this->labelY->AutoSize = true;
			this->labelY->Location = System::Drawing::Point(230, 20);
			this->labelY->Name = L"labelY";
			this->labelY->Size = System::Drawing::Size(46, 13);
			this->labelY->TabIndex = 1;
			this->labelY->Text = L"Y: 100%";
			// 
			// labelU
			// 
			this->labelU->AutoSize = true;
			this->labelU->Location = System::Drawing::Point(230, 60);
			this->labelU->Name = L"labelU";
			this->labelU->Size = System::Drawing::Size(47, 13);
			this->labelU->TabIndex = 3;
			this->labelU->Text = L"U: 100%";
			// 
			// labelV
			// 
			this->labelV->AutoSize = true;
			this->labelV->Location = System::Drawing::Point(230, 100);
			this->labelV->Name = L"labelV";
			this->labelV->Size = System::Drawing::Size(46, 13);
			this->labelV->TabIndex = 5;
			this->labelV->Text = L"V: 100%";
			// 
			// checkBoxInvert
			// 
			this->checkBoxInvert->AutoSize = true;
			this->checkBoxInvert->Location = System::Drawing::Point(20, 150);
			this->checkBoxInvert->Name = L"checkBoxInvert";
			this->checkBoxInvert->Size = System::Drawing::Size(85, 17);
			this->checkBoxInvert->TabIndex = 6;
			this->checkBoxInvert->Text = L"Invert Colors";
			this->checkBoxInvert->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBoxInvert_CheckedChanged);
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(300, 200);
			this->Controls->Add(this->trackBarY);
			this->Controls->Add(this->labelY);
			this->Controls->Add(this->trackBarU);
			this->Controls->Add(this->labelU);
			this->Controls->Add(this->trackBarV);
			this->Controls->Add(this->labelV);
			this->Controls->Add(this->checkBoxInvert);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"ToolWindow";
			this->Text = L"ToolWindow";
			this->TopMost = true;
			this->Load += gcnew System::EventHandler(this, &ToolWindow::ToolWindow_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarY))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarU))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBarV))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ToolWindow_Load(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void trackBarY_Scroll(System::Object^ sender, System::EventArgs^ e) {
	float percent = this->trackBarY->Value;
	this->labelY->Text = "Y: " + percent.ToString() + "%";
	YScale = this->trackBarY->Value;
}
private: System::Void trackBarU_Scroll(System::Object^ sender, System::EventArgs^ e) {
	float percent = this->trackBarU->Value;
	this->labelU->Text = "U: " + percent.ToString() + "%";
	UScale = this->trackBarU->Value;
}
private: System::Void trackBarV_Scroll(System::Object^ sender, System::EventArgs^ e) {
	float percent = this->trackBarV->Value;
	this->labelV->Text = "V: " + percent.ToString() + "%";
	VScale = this->trackBarV->Value;
}
private: System::Void checkBoxInvert_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

	if(checkBoxInvert->Checked)
	{
		YScale = -YScale;
		UScale = -UScale;
		VScale = -VScale;
		return;
	}
}
	   
};
}
