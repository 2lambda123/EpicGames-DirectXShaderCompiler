#pragma once

#include "dxc/Support/WinIncludes.h"

#include "dia2.h"

#include "dxc/dxcapi.h"
#include "dxc/Support/dxcapi.use.h"
#include "dxc/Support/microcom.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/SourceMgr.h"

#include "DxDiaBuffer.h"

namespace dxdia {

// Supported input types for dxdia.
enum class InputKind {
  // Input is LLVM Module (and potentially a DXIL module, doesn't matter).
  LLVM,
  // Input is a DXBC/DXIL Blob, which is queried for the following
  // parts: DXIL, PDB.
  Blob,
  // Input is HLSL source code, which is to be compiled using dxcompiler
  // (or d3dcompiler if --use-d3dcompiler is provided).
  HLSL,
  // Input is assumed to be a PDB (any PDB would work, not just the ones
  // generated by d3dcompiler).
  PDB
};

void ParseHLSLWithDXCompiler(
    dxc::DxcDllSupport &dxcompiler,
    IDxcBlob *InputBlob,
    llvm::StringRef input_filename,
    llvm::StringRef entrypoint,
    llvm::StringRef target_profile,
    IDxcBlob **ppBlob);

void ParseHLSLWithD3DCompiler(
    HMODULE d3dcompiler_dll,
    IDxcBlob *InputBlob,
    llvm::StringRef input_filename,
    llvm::StringRef entrypoint,
    llvm::StringRef target_profile,
    IDxcBlob **ppBlob);

void ExtractDxilAndPDBBlobParts(
    dxc::DxcDllSupport &dxcompiler,
    llvm::StringRef blob_str,
    IDxcBlob **ppDxil,
    IDxcBlob **ppPdb);

void ExtractDxilAndPDBBlobParts(
    dxc::DxcDllSupport &dxcompiler,
    IDxcBlob *pBlob,
    IDxcBlob **ppDxil,
    IDxcBlob **ppPdb);

void LoadLLVMModule(
    llvm::StringRef Contents,
    llvm::StringRef BufId,
    llvm::LLVMContext *Ctx,
    llvm::SMDiagnostic *Err,
    IDiaDataSource **ppDataSource);

void LoadPBD(
    llvm::StringRef input_filename,
    IDiaDataSource **ppDataSource);

}  // namespace dxdia
