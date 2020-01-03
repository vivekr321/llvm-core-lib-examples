#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Host.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Basic/DiagnosticOptions.h"
#include "clang/Basic/FileManager.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Basic/LangOptions.h"
#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/TargetOptions.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/PreprocessorOptions.h"
#include "clang/Parse/Parser.h"
#include "clang/Parse/ParseAST.h"
#include <iostream>

using namespace llvm;
using namespace clang;

static cl::opt<std::string>
FileName(cl::Positional, cl::desc("Input file"), cl::Required);

int main(int argc, char** argv)
{
    cl::ParseCommandLineOptions(argc, argv, "Compiler Front end");
    CompilerInstance ci;
    DiagnosticOptions diagnosticOptions;
    ci.createDiagnostics();

    std::shared_ptr<clang::TargetOptions> pto(new clang::TargetOptions());
    pto->Triple = sys::getDefaultTargetTriple();
    TargetInfo *pti = TargetInfo::CreateTargetInfo(ci.getDiagnostics(), pto);

    ci.setTarget(pti);

    ci.createFileManager();
    ci.createSourceManager(ci.getFileManager());
    ci.createPreprocessor(TU_Complete);
    ci.getPreprocessorOpts().UsePredefines = false;

    std::unique_ptr< clang::ASTConsumer > astConsumer = clang::CreateASTPrinter(NULL, "");
    ci.setASTConsumer(std::move(astConsumer));

    ci.createASTContext();
    ci.createSema(TU_Complete, NULL);
    llvm::ErrorOr<const FileEntry *> pFile = ci.getFileManager().getFile(FileName);
    if (!pFile) {
        std::cerr << "File not found: " << FileName << std::endl;
        return 1;
    }
    ci.getSourceManager().setMainFileID(ci.getSourceManager().createFileID(
        pFile.get(), SourceLocation(), SrcMgr::C_User));
    ci.getDiagnosticClient().BeginSourceFile(ci.getLangOpts(), 0);
    ParseAST(ci.getSema());
    ci.getASTContext().PrintStats();
    ci.getDiagnosticClient().EndSourceFile();

    return 0;
}