//=============================================================================
// Copyright (C) 2001-2005 by Computer Graphics Group, RWTH Aachen
// Copyright (C) 2011-2017 The pmp-library developers
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//=============================================================================
#pragma once
//=============================================================================

#include <pmp/SurfaceMesh.h>
#include <pmp/io/IOOptions.h>

#include <string>

//=============================================================================

namespace pmp {

//=============================================================================

//! \addtogroup io io
//! @{

//=============================================================================

//! Class for reading and writing surface meshes from and to files
class SurfaceMeshIO
{
public:

    //! Construct with default IO options
    SurfaceMeshIO(const IOOptions& options = IOOptions())
        : m_options(options){};

    //! Read surface mesh from file \c filename
    bool read(SurfaceMesh& mesh, const std::string& filename);

    //! Write surface mesh \c mesh to file \c filename
    bool write(const SurfaceMesh& mesh, const std::string& filename);

private:
    bool readOFF(SurfaceMesh& mesh, const std::string& filename);
    bool readOBJ(SurfaceMesh& mesh, const std::string& filename);
    bool readPoly(SurfaceMesh& mesh, const std::string& filename);
    bool readSTL(SurfaceMesh& mesh, const std::string& filename);

    bool writeOFF(const SurfaceMesh& mesh, const std::string& filename);
    bool writeOFFBinary(const SurfaceMesh& mesh, const std::string& filename);
    bool writeOBJ(const SurfaceMesh& mesh, const std::string& filename);
    bool writePoly(const SurfaceMesh& mesh, const std::string& filename);
    bool writeSTL(const SurfaceMesh& mesh, const std::string& filename);

private:
    IOOptions m_options;
};

//=============================================================================
//! @}
//=============================================================================
} // namespace pmp
//=============================================================================
