//#pragma OPENCL EXTENSION cl_khr_global_int32_base_atomics : enable

typedef struct{
    float4 target;
    float x;
    float y;
    float2 frc;
    float4 dummy;
    float life;
    float death;
    float2 vel;
    
    
    
    
} Particle;


static void test(int a) {
    
    
}



__kernel void resetForce(__global Particle* particles){
    
    int id = get_global_id(0);  //index which is processed by OpenCL
    __global Particle *p = &particles[id];
    p->frc = (float2)(0.0f, 0.0f);
    p->vel = (float2)(0.0f, 0.0f);
    
    p->frc.x += p->target.x;
    p->frc.y += p->target.y;
    
    
}

__kernel void addPolyObstacle(__global Particle* particles,
                              const int nvert,
                              __global float2* polys,
                              __global float4* posBuffer,
                              __global float4* colBuffer,
                              const float repRadius,
                              const float repScale
                              ){
    
    int id = get_global_id(0);  //index which is processed by OpenCL
    __global Particle *p = &particles[id];
    __global float4 *pos = &posBuffer[id];
    __global float4 *col = &colBuffer[id];
    
    
    p->frc = (float2)(0.0f, 0.0f);
    p->vel = (float2)(0.0f, 0.0f);
    
    p->frc.x += p->target.x;
    p->frc.y += p->target.y;
    

    for(int i=0; i<nvert;i++) {
        
        float2 vertex = polys[i];
        
        float2 diff = (float2)(p->x - vertex.x, p->y - vertex.y);
        float length = fast_length(diff);
        //(float)sqrt( diff.x*diff.x + diff.y*diff.y );
        
        
        //float radius = this->repRadius;
        bool bAmCloseEnough = (length < repRadius);
                   // float scale = repScale;
        if (bAmCloseEnough ){
            float pct = 1.0f - (length / repRadius);  // stronger on the inside
            //diff.normalize();
            //diff = normalize(diff);
            //float length = (float)sqrt(diff.x*diff.x + diff.y*diff.y);
           // if( length > 0 ) {
                diff /= length;
            //}
            
            
            p->frc.x = p->frc.x + diff.x * repScale * pct;
            p->frc.y = p->frc.y + diff.y * repScale * pct;
        }
        
        
        
    }
    
    
    p->vel += p->frc;
    
    float4 velConv = (float4)(p->vel.x, p->vel.y, 0.0, 0.0);
    float4 result = *pos + velConv;
    
    *pos += velConv;
    
    
    //if(id == 0 )
    //  printf("col %f", p->life / p->death);
    //float c = p->life / (p->death);
  
    float c = (p->dummy.x > 1.5) ? 1.0f : 0.50f;
    
    
    col->x = c;
    col->y = c;
    col->z = c;
    
  
    
    p->x = result.x;
    p->y = result.y;
    
    p->life ++;
    
    
    
}




__kernel void addAttractionForce(__global Particle* particles,
                                 const float2 repulsionPos
                                 
                                 ){
    
    int id = get_global_id(0);  //index which is processed by OpenCL
    __global Particle *p = &particles[id];
    
    float2 posOfForce = (float2)(repulsionPos.x, repulsionPos.y);
    
    float2 diff = (float2)(p->x - posOfForce.x, p->y - posOfForce.y);
    float length = (float)sqrt( diff.x*diff.x + diff.y*diff.y );
    
    
    float radius = 100.0f;
    bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
    
    float scale = 1.0;
    if (bAmCloseEnough == true){
        float pct = 1 - (length / radius);
        //diff.normalize();
        
        float length = (float)sqrt(diff.x*diff.x + diff.y*diff.y);
        if( length > 0 ) {
            diff.x /= length;
            diff.y /= length;
        }
        
        
        p->frc.x = p->frc.x - diff.x * scale * pct;
        p->frc.y = p->frc.y - diff.y * scale * pct;
    }
    
    
}

__kernel void addRepulsionForce(__global Particle* particles,
                                const float2 repulsionPos
                                
                                ){
    
    int id = get_global_id(0);  //index which is processed by OpenCL
    __global Particle *p = &particles[id];
    
    float2 posOfForce = (float2)(repulsionPos.x, repulsionPos.y);
    
    float2 diff = (float2)(p->x - posOfForce.x, p->y - posOfForce.y);
    float length = (float)sqrt( diff.x*diff.x + diff.y*diff.y );
    
    
    float radius = 100.0f;
    bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
    
    float scale = 4.0;
    if (bAmCloseEnough == true){
        float pct = 1 - (length / radius);  // stronger on the inside
        //diff.normalize();
        
        float length = (float)sqrt(diff.x*diff.x + diff.y*diff.y);
        if( length > 0 ) {
            diff.x /= length;
            diff.y /= length;
        }
        
        
        p->frc.x = p->frc.x + diff.x * scale * pct;
        p->frc.y = p->frc.y + diff.y * scale * pct;
    }
    
    
}




__kernel void update(__global Particle* particles,
                     __global float4* posBuffer,
                     __global float4* colBuffer
                     ){
    
    int id = get_global_id(0);  //index which is processed by OpenCL
    __global Particle *p = &particles[id];
    __global float4 *pos = &posBuffer[id];
    __global float4 *col = &colBuffer[id];
    
    
    // p->frc = (float2)(0.0f, 0.0f);
    
    // add force
    
    
    
    
    
    
    
    
    
    // update
    
    
    /*
     
     bool bDampedOnCollision = true;
     bool bDidICollide = false;
     // what are the walls
     float minx = 0;
     float miny = 0;
     float maxx = 1440;
     float maxy = 900;
     
     if (p->x > maxx){
     pos->x = maxx; // move to the edge, (important!)
     p->vel.x *= -1;
     bDidICollide = true;
     } else if (p->x< minx){
     pos->x = minx; // move to the edge, (important!)
     p->vel.x *= -1;
     bDidICollide = true;
     }
     
     if (p->y > maxy){
     pos->y = maxy; // move to the edge, (important!)
     p->vel.y *= -1;
     bDidICollide = true;
     } else if (p->y < miny){
     pos->y = miny; // move to the edge, (important!)
     p->vel.y *= -1;
     bDidICollide = true;
     }
     
     if (bDidICollide == true && bDampedOnCollision == true){
     //float2 mult = (float2)(0.3f, 0.3f);
     //p->vel *= mult;
     
     p->frc = (float2)(0.0f, 0.0f);
     // pos->x = 900.0;
     //pos->y = 450.0;
     
     
     }
     */
    
    
    p->vel += p->frc;
    
    float4 velConv = (float4)(p->vel.x, p->vel.y, 0.0, 0.0);
    float4 result = *pos + velConv;
    
    *pos += velConv;
    
    
    //if(id == 0 )
    //  printf("col %f", p->life / p->death);
    //float c = p->life / (p->death);
    
    float c = 1.0f;
    
    //if(p->life < 2 )
      //  c = 1;
    
    col->x = c;
    col->y = c;
    col->z = c;
    
    p->x = result.x;
    p->y = result.y;
    
    p->life ++;
    
    
    
    
    
}
