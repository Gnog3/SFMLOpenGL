#include "StaticBlockFragment.hpp"

void StaticBlockFragment::addBlock(sf::Vector3i position) {
    blocks.push_back(position);
    
    vertexData.reserve(vertexData.size() + 6 * 6 * 8);
    
    vertexData.push_back(position.x);
    vertexData.push_back(position.y);
    vertexData.push_back(position.z);
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( -1 );
    
    vertexData.push_back(position.x);
    vertexData.push_back(position.y + 1);
    vertexData.push_back(position.z);
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( -1 );
    
    vertexData.push_back(position.x + 1);
    vertexData.push_back(position.y);
    vertexData.push_back(position.z);
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( -1 );
    
    vertexData.push_back(position.x + 1);
    vertexData.push_back(position.y + 1);
    vertexData.push_back(position.z);
    vertexData.push_back( 1 );
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( -1 );
    
    vertexData.push_back(position.x + 1);
    vertexData.push_back(position.y);
    vertexData.push_back(position.z);
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( -1 );
    
    vertexData.push_back(position.x);
    vertexData.push_back(position.y + 1);
    vertexData.push_back(position.z);
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( -1 );
    
    vertexData.push_back(position.x);
    vertexData.push_back(position.y);
    vertexData.push_back(position.z);
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( -1 );
    vertexData.push_back( 0 );
    
    vertexData.push_back(position.x);
    vertexData.push_back(position.y);
    vertexData.push_back(position.z + 1);
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( -1 );
    vertexData.push_back( 0 );
    
    vertexData.push_back(position.x + 1);
    vertexData.push_back(position.y);
    vertexData.push_back(position.z);
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( -1 );
    vertexData.push_back( 0 );
    
    vertexData.push_back(position.x + 1);
    vertexData.push_back(position.y);
    vertexData.push_back(position.z + 1);
    vertexData.push_back( 1 );
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( -1 );
    vertexData.push_back( 0 );
    
    vertexData.push_back(position.x + 1);
    vertexData.push_back(position.y);
    vertexData.push_back(position.z);
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( -1 );
    vertexData.push_back( 0 );
    
    vertexData.push_back(position.x);
    vertexData.push_back(position.y);
    vertexData.push_back(position.z + 1);
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( -1 );
    vertexData.push_back( 0 );
    
    vertexData.push_back(position.x);
    vertexData.push_back(position.y);
    vertexData.push_back(position.z);
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( -1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    
    vertexData.push_back(position.x);
    vertexData.push_back(position.y);
    vertexData.push_back(position.z + 1);
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    vertexData.push_back( -1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    
    vertexData.push_back(position.x);
    vertexData.push_back(position.y + 1);
    vertexData.push_back(position.z);
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( -1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    
    vertexData.push_back(position.x);
    vertexData.push_back(position.y + 1);
    vertexData.push_back(position.z + 1);
    vertexData.push_back( 1 );
    vertexData.push_back( 1 );
    vertexData.push_back( -1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    
    vertexData.push_back(position.x);
    vertexData.push_back(position.y + 1);
    vertexData.push_back(position.z);
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( -1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    
    vertexData.push_back(position.x);
    vertexData.push_back(position.y);
    vertexData.push_back(position.z + 1);
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    vertexData.push_back( -1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    
    vertexData.push_back(position.x + 1);
    vertexData.push_back(position.y + 1);
    vertexData.push_back(position.z + 1);
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    
    vertexData.push_back(position.x + 1);
    vertexData.push_back(position.y);
    vertexData.push_back(position.z + 1);
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    
    vertexData.push_back(position.x);
    vertexData.push_back(position.y + 1);
    vertexData.push_back(position.z + 1);
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    
    vertexData.push_back(position.x);
    vertexData.push_back(position.y);
    vertexData.push_back(position.z + 1);
    vertexData.push_back( 1 );
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    
    vertexData.push_back(position.x);
    vertexData.push_back(position.y + 1);
    vertexData.push_back(position.z + 1);
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    
    vertexData.push_back(position.x + 1);
    vertexData.push_back(position.y);
    vertexData.push_back(position.z + 1);
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    
    vertexData.push_back(position.x + 1);
    vertexData.push_back(position.y + 1);
    vertexData.push_back(position.z + 1);
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    
    vertexData.push_back(position.x + 1);
    vertexData.push_back(position.y + 1);
    vertexData.push_back(position.z);
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    
    vertexData.push_back(position.x);
    vertexData.push_back(position.y + 1);
    vertexData.push_back(position.z + 1);
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    
    vertexData.push_back(position.x);
    vertexData.push_back(position.y + 1);
    vertexData.push_back(position.z);
    vertexData.push_back( 1 );
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    
    vertexData.push_back(position.x);
    vertexData.push_back(position.y + 1);
    vertexData.push_back(position.z + 1);
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    
    vertexData.push_back(position.x + 1);
    vertexData.push_back(position.y + 1);
    vertexData.push_back(position.z);
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    
    vertexData.push_back(position.x + 1);
    vertexData.push_back(position.y + 1);
    vertexData.push_back(position.z + 1);
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    
    vertexData.push_back(position.x + 1);
    vertexData.push_back(position.y + 1);
    vertexData.push_back(position.z);
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    
    vertexData.push_back(position.x + 1);
    vertexData.push_back(position.y);
    vertexData.push_back(position.z + 1);
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    
    vertexData.push_back(position.x + 1);
    vertexData.push_back(position.y);
    vertexData.push_back(position.z);
    vertexData.push_back( 1 );
    vertexData.push_back( 1 );
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );    vertexData.push_back(position.x + 1);
    vertexData.push_back(position.y);
    vertexData.push_back(position.z + 1);
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
    
    vertexData.push_back(position.x + 1);
    vertexData.push_back(position.y + 1);
    vertexData.push_back(position.z);
    vertexData.push_back( 0 );
    vertexData.push_back( 1 );
    vertexData.push_back( 1 );
    vertexData.push_back( 0 );
    vertexData.push_back( 0 );
}
size_t StaticBlockFragment::getSize() {
    return vertexData.size();
}
std::vector<float>& StaticBlockFragment::getVertices() { return vertexData; }
