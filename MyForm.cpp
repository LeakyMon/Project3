#include "MyForm.h"
//#include "LoadingForm.h"


void main(array<System::String^>^ args) {

    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

  
    CustomUnorderedMap obj;
    obj = obj.getMap();
    //obj.InitializeStockMap();
    while (true) {

        Project3::MyForm^ form = gcnew Project3::MyForm(obj);  
        form->GetFormInstance();
     
        if (form->GetFormInstance()->ShowDialog() == System::Windows::Forms::DialogResult::OK)
        {

            form->Close();
            Project3::MyForm^ newForm = gcnew Project3::MyForm(obj);
            // Show the new instance of the form.
            newForm->ShowDialog();
        }
        else {
            break;
        }
    }
  
}
