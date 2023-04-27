#include "MyForm.h"
//#include "LoadingForm.h"


void main(array<System::String^>^ args) {

    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

  

    while (true) {

        Project3::MyForm^ form = gcnew Project3::MyForm();  
        form->GetFormInstance();
     
        if (form->GetFormInstance()->ShowDialog() == System::Windows::Forms::DialogResult::OK)
        {

            form->Close();
            Project3::MyForm^ newForm = gcnew Project3::MyForm();
            // Show the new instance of the form.
            newForm->ShowDialog();
        }
        else {
            break;
        }
    }
	//Application::Run(gcnew Project3::MyForm());
  

 
}
