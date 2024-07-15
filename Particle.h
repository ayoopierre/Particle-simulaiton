#ifndef PARTICLE_H_
#define PARTICLE_H_

struct Particle{//struct is same as class, but is automaticly public
    double m_x;
    double m_y;
    double m_speed;
    double m_direction;
    double xspeed;
    double yspeed;
    void update(int interval);
    Particle();
    virtual ~Particle();
};
#endif
