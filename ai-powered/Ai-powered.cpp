#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tensorflow/lite/interpreter.h>
#include <tensorflow/lite/model.h>
#include <tensorflow/lite/kernels/register.h>
#include <wx/wx.h>

// Function to load input text and convert to tensor
std::vector<int> tokenizeText(const std::string& text) {
    std::vector<int> tokens;
    for (char c : text) {
        tokens.push_back(static_cast<int>(c));  // Simple char-to-int conversion
    }
    return tokens;
}

// Load TensorFlow Lite model
std::unique_ptr<tflite::Interpreter> loadModel(const std::string& modelPath) {
    std::unique_ptr<tflite::FlatBufferModel> model = tflite::FlatBufferModel::BuildFromFile(modelPath.c_str());
    tflite::ops::builtin::BuiltinOpResolver resolver;
    std::unique_ptr<tflite::Interpreter> interpreter;

    tflite::InterpreterBuilder(*model, resolver)(&interpreter);
    interpreter->AllocateTensors();
    return interpreter;
}

// Run Sentiment Prediction
std::string predictSentiment(tflite::Interpreter* interpreter, const std::string& text) {
    auto tokens = tokenizeText(text);
    
    // Copy tokens to input tensor
    float* inputTensor = interpreter->typed_input_tensor<float>(0);
    for (size_t i = 0; i < tokens.size(); ++i) {
        inputTensor[i] = tokens[i];
    }

    // Run inference
    interpreter->Invoke();

    // Get output tensor (probability of sentiment classes)
    float* outputTensor = interpreter->typed_output_tensor<float>(0);
    
    // Determine sentiment class
    int sentimentIndex = std::distance(outputTensor, std::max_element(outputTensor, outputTensor + 3));
    
    if (sentimentIndex == 0) return "Negative";
    else if (sentimentIndex == 1) return "Neutral";
    else return "Positive";
}

// wxWidgets Application: Sentiment Analysis App
class SentimentApp : public wxApp {
public:
    virtual bool OnInit();
};

class SentimentFrame : public wxFrame {
public:
    SentimentFrame(const wxString& title);

private:
    void OnAnalyzeSentiment(wxCommandEvent& event);
    
    wxTextCtrl* inputTextCtrl;
    wxStaticText* resultTextCtrl;
    std::unique_ptr<tflite::Interpreter> interpreter;
};

bool SentimentApp::OnInit() {
    // Load TensorFlow Lite model
    interpreter = loadModel("text_classification.tflite");

    SentimentFrame* frame = new SentimentFrame("Sentiment Analysis");
    frame->Show(true);
    return true;
}

SentimentFrame::SentimentFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300)) {

    // Create GUI elements
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    inputTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(350, 50), wxTE_MULTILINE);
    resultTextCtrl = new wxStaticText(panel, wxID_ANY, "Predicted Sentiment: ", wxDefaultPosition, wxSize(350, 20));

    wxButton* analyzeButton = new wxButton(panel, wxID_ANY, "Analyze Sentiment");
    analyzeButton->Bind(wxEVT_BUTTON, &SentimentFrame::OnAnalyzeSentiment, this);

    vbox->Add(inputTextCtrl, 0, wxALL | wxEXPAND, 10);
    vbox->Add(analyzeButton, 0, wxALL | wxCENTER, 10);
    vbox->Add(resultTextCtrl, 0, wxALL | wxEXPAND, 10);

    panel->SetSizer(vbox);
}

void SentimentFrame::OnAnalyzeSentiment(wxCommandEvent& event) {
    std::string userText = inputTextCtrl->GetValue().ToStdString();
    std::string sentiment = predictSentiment(interpreter.get(), userText);
    resultTextCtrl->SetLabel("Predicted Sentiment: " + wxString(sentiment));
}

wxIMPLEMENT_APP(SentimentApp);
