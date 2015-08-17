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


__kernel void update(__global Particle* particles,
                              const int nvert,
                              __global float2* polys,
                              __global float4* posBuffer,
                              __global float4* colBuffer,
                              const float repRadius,
                              const float repScale
                              ){
    
    
    int id                  = get_global_id(0);
    __global Particle *p    = &particles[id];
    __global float4 *pos    = &posBuffer[id];
    __global float4 *col    = &colBuffer[id];
    
    
    p->frc      = (float2)(0.0f, 0.0f);
    p->vel      = (float2)(0.0f, 0.0f);
    
    p->frc.x    += p->target.x;
    p->frc.y    += p->target.y;
    

    for(int i=0; i<nvert;i++) {
        
        float2 vertex = polys[i];
        
        float2 diff = (float2)(p->x - vertex.x, p->y - vertex.y);
        float length = fast_length(diff);
        bool bAmCloseEnough = (length < repRadius);
        
        if (bAmCloseEnough ) {
            
            float pct = 1.0f - (length / repRadius);
            diff /= length;
            
            p->frc.x = p->frc.x + diff.x * repScale * pct;
            p->frc.y = p->frc.y + diff.y * repScale * pct;
            
        }
        
    }
    
    p->vel += p->frc;
    
    float4 velConv = (float4)(p->vel.x, p->vel.y, 0.0, 0.0);
    float4 result = *pos + velConv;
    
    *pos += velConv;
    
    // TODO finish colors
    
    //if(id == 0 )
    //  printf("col %f", p->life / p->death);
    //float c = p->life / (p->death);
    
    // birth
    
    float step = (float)p->death / 3.0f;
    float pct = 1.0;
    float dyingStep = p->death - step;

    
    if(p->life < step) {
        pct = (float)p->life / step;
        
    } else if(p->life > dyingStep ) {
    
            pct = (p->life - dyingStep)  / step;
            pct = 1.0 - pct;
            
        
    }
    
  

    
  
    float c = pct * p->dummy.x;
    
    
    col->x = c;
    col->y = c;
    col->z = c;
    
    p->x = result.x;
    p->y = result.y;
    
    p->life ++;
    
    
}
