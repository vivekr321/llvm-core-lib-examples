#include "llvm/Bitcode/BitcodeReader.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/raw_os_ostream.h"
#include "llvm/Support/Error.h"
#include <iostream>

using namespace llvm;

static cl::opt<std::string> FileName(cl::Positional, cl::desc("Bitcode file"), cl::Required);

int main(int argc, char** argv) {
  cl::ParseCommandLineOptions(argc, argv, "LLVM hello world\n");
  LLVMContext context;
  std::string error;

  ErrorOr<std::unique_ptr<MemoryBuffer>> mb = MemoryBuffer::getFile(FileName);
  if (std::error_code ec = mb.getError()) {
      errs() << ec.message();
      return -1;
  }

  auto m = parseBitcodeFile(mb->get()->getMemBufferRef(), context);
  if (!m) {
    std::cerr << "Error reading bitcode: " << std::endl;
    return -1;
  }

  raw_os_ostream O(std::cout);
  for (Module::const_iterator i = m->get()->getFunctionList().begin(),
    e = m->get()->getFunctionList().end(); i != e; ++i) {
    if (!i->isDeclaration())
    {
      O << i->getName() << " has " << i->size() << " basic block(s) and accepts " << i->arg_size() << " arguments \n";
    }
  }
  return 0;
}