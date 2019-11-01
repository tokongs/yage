#include <VertexBuffer.h>

namespace yage {

    VertexBuffer::VertexBuffer() {

    }

    VertexBuffer::VertexBuffer(VertexBufferDesc desc, std::vector<Vertex> data, std::vector<unsigned int> indices) {
        mBufferDesc = desc;
        glGenVertexArrays(1, &mVaoObjectId);
        YAGE_INFO("Created Vertex Array Object, ID: " + std::to_string(mVaoObjectId));

        mIndexBuffer = new IndexBuffer(indices);

        bind();
        glGenBuffers(1, &mVbObjectId);
        glBindBuffer(GL_ARRAY_BUFFER, mVbObjectId);
        YAGE_INFO("Created Vertex Buffer Object, ID: " + std::to_string(mVbObjectId));

        //calculate size of one vertex
        int size_of_vertex = sizeOfVertex(desc);
        mSize = data.size();

        int buffer_size = size_of_vertex / sizeof(float) * data.size();
        float *buffer = new float[buffer_size];

        cleanData(desc, data, buffer);

        if (desc.keepShadowBuffer)
            mShadowCopy = std::vector<float>(buffer, buffer + buffer_size);

        glBufferData(GL_ARRAY_BUFFER, buffer_size * sizeof(float), buffer, GL_STATIC_DRAW);
        setupVao(desc);

        unbind();
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        //Save a copy of the buffer to normal memory

        delete[] buffer;
    }

    VertexBuffer::~VertexBuffer() {
        delete mIndexBuffer;
        YAGE_INFO("Deleting Vertex Buffer Object, ID: " + std::to_string(mVbObjectId));
        glDeleteBuffers(1, &mVbObjectId);
        YAGE_INFO("Deleting Vertex Array Object, ID: " + std::to_string(mVaoObjectId));
        glDeleteVertexArrays(1, &mVaoObjectId);
    }

    void VertexBuffer::bind() {
        mIndexBuffer->bind();
        glBindVertexArray(mVaoObjectId);
    }

    void VertexBuffer::unbind() {
        glBindVertexArray(0);
    }

    void VertexBuffer::attachIndexBuffer(IndexBuffer* index_buffer) {
        YAGE_INFO("Attaching Index Buffer Object " + std::to_string(index_buffer->getGlId()) +
                  " to Vertex Array Object " + std::to_string(mVaoObjectId));
        bool m_indexed = true;
        bind();
        index_buffer->bind();
        unbind();
        index_buffer->unbind();
    }

    void VertexBuffer::cleanData(VertexBufferDesc desc, std::vector<Vertex> data, float *result) {
        int num_elements = sizeOfVertex(desc) / sizeof(float);

        //fill the array with only populated values
        for (int i = 0; i < data.size(); i++) {
            int offset = 0;
            if (desc.hasPosition) {
                result[i * num_elements + offset] = data[i].position.x;
                offset++;
                result[i * num_elements + offset] = data[i].position.y;
                offset++;
                result[i * num_elements + offset] = data[i].position.z;
                offset++;
            }
            if (desc.hasNormal) {
                result[i * num_elements + offset] = data[i].normal.x;
                offset++;
                result[i * num_elements + offset] = data[i].normal.y;
                offset++;
                result[i * num_elements + offset] = data[i].normal.z;
                offset++;
            }
            if (desc.hasColor) {
                result[i * num_elements + offset] = data[i].color.x;
                offset++;
                result[i * num_elements + offset] = data[i].color.y;
                offset++;
                result[i * num_elements + offset] = data[i].color.z;
                offset++;
            }
            if (desc.hasTexCoord) {
                result[i * num_elements + offset] = data[i].texCoord.x;
                offset++;
                result[i * num_elements + offset] = data[i].texCoord.y;
                offset++;
            }
            if (desc.hasBones) {
                result[i * num_elements + offset] = (float) data[i].boneId.x;
                offset++;
                result[i * num_elements + offset] = (float) data[i].boneId.y;
                offset++;
                result[i * num_elements + offset] = (float) data[i].boneId.z;
                offset++;
                result[i * num_elements + offset] = (float) data[i].boneId.w;
                offset++;
                result[i * num_elements + offset] = data[i].boneWeight.x;
                offset++;
                result[i * num_elements + offset] = data[i].boneWeight.y;
                offset++;
                result[i * num_elements + offset] = data[i].boneWeight.z;
                offset++;
                result[i * num_elements + offset] = data[i].boneWeight.w;
                offset++;
            }
        }
    }

    void VertexBuffer::setupVao(VertexBufferDesc desc) {
        bind();

        int stride = sizeOfVertex(desc);
        int offset = 0;
        if (desc.hasPosition) {
            glEnableVertexAttribArray(POSITION_BUFFER_INDEX);
            glVertexAttribPointer(POSITION_BUFFER_INDEX, 3, GL_FLOAT, false, stride, (const void *) offset);
            offset = 3 * sizeof(float);
        }
        if (desc.hasNormal) {
            glEnableVertexAttribArray(NORMAL_BUFFER_INDEX);
            glVertexAttribPointer(NORMAL_BUFFER_INDEX, 3, GL_FLOAT, false, stride, (const void *) offset);
            offset += 3 * sizeof(float);
        }
        if (desc.hasColor) {
            glEnableVertexAttribArray(COLOR_BUFFER_INDEX);
            glVertexAttribPointer(COLOR_BUFFER_INDEX, 3, GL_FLOAT, false, stride, (const void *) offset);
            offset += 3 * sizeof(float);
        }
        if (desc.hasTexCoord) {
            glEnableVertexAttribArray(TEX_COORD_BUFFER_INDEX);
            glVertexAttribPointer(TEX_COORD_BUFFER_INDEX, 2, GL_FLOAT, false, stride, (const void *) offset);
            offset += 2 * sizeof(float);
        }
        if (desc.hasBones) {
            glEnableVertexAttribArray(BONE_ID_BUFFER_INDEX);
            glVertexAttribPointer(BONE_ID_BUFFER_INDEX, 3, GL_FLOAT, false, stride, (const void *) offset);
            offset += 4 * sizeof(float);
            glEnableVertexAttribArray(BONE_WEIGHT_BUFFER_INDEX);
            glVertexAttribPointer(BONE_WEIGHT_BUFFER_INDEX, 3, GL_FLOAT, false, stride, (const void *) offset);
            offset += 4 * sizeof(float);
        }
    }

    int VertexBuffer::sizeOfVertex(VertexBufferDesc desc) {
        int size = 0;
        if (desc.hasPosition)
            size += 3 * sizeof(float);
        if (desc.hasNormal)
            size += 3 * sizeof(float);
        if (desc.hasColor)
            size += 3 * sizeof(float);
        if (desc.hasTexCoord)
            size += 2 * sizeof(float);
        if (desc.hasBones)
            size += 8 * sizeof(float);

        return size;
    }

    IndexBuffer *VertexBuffer::getIndexBuffer() {
        return mIndexBuffer;
    }

    unsigned int VertexBuffer::getSize() {
        return mSize;
    }

} // namespace yage
