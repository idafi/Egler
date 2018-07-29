#pragma once

#include <fbxsdk.h>
#include "../Egler.Core/Logging/Logging.hpp"
#include "../Egler.Core/Video/Video.hpp"

namespace Egler::Video
{
    class EGAPI FBXImporter
    {
        public:
            FBXImporter();
            ~FBXImporter();

            void ImportModel(char const * const filePath, ModelData * const data);

        private:
            FbxManager *fbxMan;
            FbxImporter *importer;
            FbxScene *scene;

            const FbxMesh * const LocateMesh(FbxNode * const node);
            void FillData(const FbxMesh * const mesh, const FbxAMatrix& transform, ModelData * const data);
            void FillPositions(const FbxMesh * const mesh, const FbxAMatrix& transform, ModelData * const data);
            void FillIndices(const FbxMesh * const mesh, ModelData * const data);
            void FillColors(const FbxMesh * const mesh, ModelData * const data);
    };

    _DefineException(FBXException)
}