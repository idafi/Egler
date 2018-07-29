#include "FBXImporter.hpp"

using namespace Egler::Logging;

namespace Egler::Video
{
    FBXImporter::FBXImporter()
    {
        fbxMan = FbxManager::Create();
        importer = FbxImporter::Create(fbxMan, "");
        scene = FbxScene::Create(fbxMan, "scene");

        FbxIOSettings *ioSettings = FbxIOSettings::Create(fbxMan, IOSROOT);
		fbxMan->SetIOSettings(ioSettings);
    }

    FBXImporter::~FBXImporter()
	{
        importer->Destroy();
		fbxMan->Destroy();
	}

    void FBXImporter::ImportModel(char const * const filePath, ModelData * const data)
    {
        LogNote("importing FBX model...");

        CheckPtr(filePath);
        CheckPtr(data);

        if(!importer->Initialize(filePath, -1, fbxMan->GetIOSettings()))
        { throw FBXException("FBX importer failed to initialize\n\t%s", importer->GetStatus().GetErrorString()); }

        scene->Clear();
        if(!importer->Import(scene))
        { throw FBXException("Failed to import FBX scene\n\t%s", importer->GetStatus().GetErrorString()); }

        const FbxMesh * const mesh = LocateMesh(scene->GetRootNode());
        if(!mesh)
        { throw FBXException("FBX scene does not contain a mesh."); }

        // use meter as base unit; use OpenGL coordinate system
        FbxSystemUnit::m.ConvertScene(scene);
        FbxAxisSystem sys(FbxAxisSystem::OpenGL);
        sys.ConvertScene(scene);

        FbxNode *node = mesh->GetNode();
        FbxAMatrix transform = node->EvaluateGlobalTransform();

        FillData(mesh, transform, data);
    }

    const FbxMesh * const FBXImporter::LocateMesh(FbxNode * const node)
    {
        CheckPtr(node);

        const FbxMesh *m = node->GetMesh();
        if(m)
        { return m; }

        int childCount = node->GetChildCount();
		if(childCount > 0)
		{
			for(int i = 0; i < childCount; i++)
			{
				m = LocateMesh(node->GetChild(i));
				if(m)
				{ return m; }
			}
		}
		
		return NULL;
    }

    void FBXImporter::FillData(const FbxMesh * const mesh, const FbxAMatrix& transform, ModelData * const data)
    {
        CheckPtr(mesh);
        CheckPtr(data);

        data->VertexCount = mesh->GetControlPointsCount();
        data->IndexCount = mesh->GetPolygonVertexCount();

        FillPositions(mesh, transform, data);
        FillIndices(mesh, data);
        FillColors(mesh, data);
    }

    void FBXImporter::FillPositions(const FbxMesh * const mesh, const FbxAMatrix& transform, ModelData * const data)
    {
        CheckPtr(mesh);
        CheckPtr(data);

		const FbxVector4 * const fbxPositions = mesh->GetControlPoints();

		for(int i = 0; i < data->VertexCount; i++)
		{
			// apply node transform
			FbxVector4 fbxPoint = fbxPositions[i];
			fbxPoint = transform.MultT(fbxPoint);

			int baseIndex = i * 3;
			data->VertexPositions[baseIndex] = (float)(fbxPoint[0]);
			data->VertexPositions[baseIndex + 1] = (float)(fbxPoint[1]);
			data->VertexPositions[baseIndex + 2] = (float)(fbxPoint[2]);
		}
    }

    void FBXImporter::FillIndices(const FbxMesh * const mesh, ModelData * const data)
    {
        CheckPtr(mesh);
        CheckPtr(data);

		const int * const fbxIndices = mesh->GetPolygonVertices();

		for(int i = 0; i < data->IndexCount; i++)
		{ data->Indices[i] = fbxIndices[i]; }
    }

    void FBXImporter::FillColors(const FbxMesh * const mesh, ModelData * const data)
    {
        CheckPtr(mesh);
        CheckPtr(data);

		const FbxGeometryElementVertexColor * const colorElement = mesh->GetElementVertexColor();

		for(int i = 0; i < data->IndexCount; i++)
		{
			int index = data->Indices[i];

			// the source color is grabbed directly from each source vertex...
			int colorIndex = colorElement->GetIndexArray().GetAt(i);
			FbxColor fbxCol = colorElement->GetDirectArray().GetAt(colorIndex);

			// ...but it's mapped to a specific destination vertex via the vertex's array index
			int baseI = index * 4;
			data->VertexColors[baseI] = (float)(fbxCol.mRed);
			data->VertexColors[baseI + 1] = (float)(fbxCol.mGreen);
			data->VertexColors[baseI + 2] = (float)(fbxCol.mBlue);
			data->VertexColors[baseI + 3] = (float)(fbxCol.mAlpha);
		}
    }
}