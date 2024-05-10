//////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2016, Image Engine Design Inc. All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are
//  met:
//
//      * Redistributions of source code must retain the above
//        copyright notice, this list of conditions and the following
//        disclaimer.
//
//      * Redistributions in binary form must reproduce the above
//        copyright notice, this list of conditions and the following
//        disclaimer in the documentation and/or other materials provided with
//        the distribution.
//
//      * Neither the name of John Haddon nor the names of
//        any other contributors to this software may be used to endorse or
//        promote products derived from this software without specific prior
//        written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
//  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
//  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
//  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "GafferScene/Export.h"
#include "GafferScene/TypeIds.h"

#include "Gaffer/Plug.h"
#include "Gaffer/ValuePlug.h"

#include "IECoreScene/ShaderNetwork.h"

#include "IECore/CompoundObject.h"

namespace GafferScene
{

/// Plug that accepts a Shader::outPlug() as input, and provides
/// access to the shading network generated by the shader.
class GAFFERSCENE_API ShaderPlug : public Gaffer::Plug
{

	public :

		explicit ShaderPlug( const std::string &name=defaultName<ShaderPlug>(), Direction direction=In, unsigned flags=Default );
		~ShaderPlug() override;

		GAFFER_PLUG_DECLARE_TYPE( GafferScene::ShaderPlug, ShaderPlugTypeId, Plug );

		bool acceptsChild( const Gaffer::GraphComponent *potentialChild ) const override;
		Gaffer::PlugPtr createCounterpart( const std::string &name, Direction direction ) const override;
		bool acceptsInput( const Gaffer::Plug *input ) const override;

		/// Returns a hash representing the shading network generated
		/// by the input shader.
		IECore::MurmurHash attributesHash() const;
		/// Returns the attributes representing the shading network
		/// generated by the input shader.
		IECore::ConstCompoundObjectPtr attributes() const;

		/// Returns the plug responsible for authoring the specified parameter
		/// within a shader network obtained by a call to attributes().
		const Gaffer::ValuePlug *parameterSource( const IECoreScene::ShaderNetwork::Parameter &parameter) const;
		Gaffer::ValuePlug *parameterSource( const IECoreScene::ShaderNetwork::Parameter &parameter );

	private:

		const Gaffer::Plug *shaderOutPlug() const;

};

IE_CORE_DECLAREPTR( ShaderPlug );

} // namespace GafferScene
