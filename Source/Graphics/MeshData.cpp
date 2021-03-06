#include "MeshData.h"

MeshData::MeshData()
{
	VB = 0;
	IB = 0;
	NumIndices = 0;
	MaterialIndex = 0;
	VAO = 0;
}

MeshData::~MeshData()
{
	clear();
}

void MeshData::clear()
{
	printf("Deleting Mesh %d %d\n", (int)VB, (int)IB);
	
	// Disable the two vertex array attributes.
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	// Release the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VB);

	//Index Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &IB);

	mVertices.clear();
	
	debugOpengl("Deleting Mesh... MeshData::clear()");
}

bool MeshData::init(const std::vector<Vertex>& verts, const std::vector<unsigned int>& inds)
{
	clear();

	mVertices = verts;
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VB);
	glBindVertexArray(VAO);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*verts.size(), &verts[0], GL_STATIC_DRAW);

	/*for (int i = Vertices.size()-1;i >=0;i--)
	{
	printf("added %f %f %f\n", Vertices[i].Pos.x, Vertices[i].Pos.y, Vertices[i].Pos.z);
	}*/

	// Generate an ID for the index buffer.
	glGenBuffers(1, &IB);

	// Bind the index buffer and load the index data into it.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, inds.size() * sizeof(unsigned int), &inds[0], GL_STATIC_DRAW);

	NumIndices = inds.size();
	printf("Creating Mesh %d %d, Size: %d %d\n", (int)VB, (int)IB, (int)verts.size(), (int)inds.size());
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	debugOpengl("Creating Mesh... MeshData::init()");
	
	return true;
}

void MeshData::render()
{
	debugOpengl("Prep Draw, MeshData::render()");
	
	assert(VB!=0 && IB!=0);
	
	glBindVertexArray(VAO);
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, Pos));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, UV));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, Normal));
	debugOpengl("Pre Draw, MeshData::render()");
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	//printf("4 %d, using buffers %d and %d\n", mEntries[i].NumIndices, mEntries[i].VB, mEntries[i].IB);
	//printf("Mesh ptr draw: %d\n", this);
	//const unsigned int MaterialIndex = m_Entries[i].MaterialIndex;

	//if (MaterialIndex < m_Textures.size() && m_Textures[MaterialIndex]) {
	//	//m_Textures[MaterialIndex]->bind(GL_TEXTURE0);
	//	//m_Textures[MaterialIndex]->bind();
	//}
	
	glDrawElements(GL_TRIANGLES, NumIndices, GL_UNSIGNED_INT, 0);

	debugOpengl("Post Draw, MeshData::render()");

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	
	glBindVertexArray(0);
}

MeshDataTexture3D::MeshDataTexture3D()
{
	VB = 0;
	IB = 0;
	NumIndices = 0;
	MaterialIndex = 0;
}

MeshDataTexture3D::~MeshDataTexture3D()
{
	clear();
}

void MeshDataTexture3D::clear()
{
	// Disable the two vertex array attributes.
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	// Release the vertex buffer.
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VB);

	//Index Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &IB);
}

bool MeshDataTexture3D::Init(const std::vector<VertexTex3D>& Vertices, const std::vector<unsigned int>& Indices)
{
	clear();

	glGenBuffers(1, &VB);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, VB);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexTex3D)*Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

	/*for (int i = Vertices.size()-1;i >=0;i--)
	{
	printf("added %f %f %f\n", Vertices[i].Pos.x, Vertices[i].Pos.y, Vertices[i].Pos.z);
	}*/

	// Generate an ID for the index buffer.
	glGenBuffers(1, &IB);

	// Bind the index buffer and load the index data into it.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), &Indices[0], GL_STATIC_DRAW);

	NumIndices = Indices.size();
	return true;
}

void MeshDataTexture3D::render()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	//glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexTex3D), (const GLvoid*)offsetof(VertexTex3D, Pos));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexTex3D), (const GLvoid*)offsetof(VertexTex3D, UV));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexTex3D), (const GLvoid*)offsetof(VertexTex3D, Normal));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	//printf("4 %d, using buffers %d and %d\n", mEntries[i].NumIndices, mEntries[i].VB, mEntries[i].IB);
	//printf("Mesh ptr draw: %d\n", this);
	//const unsigned int MaterialIndex = m_Entries[i].MaterialIndex;

	//if (MaterialIndex < m_Textures.size() && m_Textures[MaterialIndex]) {
	//	//m_Textures[MaterialIndex]->bind(GL_TEXTURE0);
	//	//m_Textures[MaterialIndex]->bind();
	//}
	glDrawElements(GL_TRIANGLES, NumIndices, GL_UNSIGNED_INT, 0);

	//debugOpengl("mesh entry 2d array draw");
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	//glDisableVertexAttribArray(3);
}
