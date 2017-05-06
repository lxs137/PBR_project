#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <cstring>
#include "shape/polygon.h"
#include "util/file_util/file_helper.h"
#include "sampler/disk_sampler.h"
#include "sampler/multi_class_disk.h"
int main(int argv, char** argc)
{
    const int CLASS_N = 5;
    const int RESOLUTION = 500;

    float min_dis[CLASS_N] = {0.08f, 0.03f, 0.03f, 0.03f, 0.04f};
    MultiClassDiskSampler sampler = MultiClassDiskSampler(0, 1, 0, 1, CLASS_N, min_dis);
    int pixel_size = RESOLUTION * RESOLUTION * 3;
    int **rgb;
    rgb = new int* [pixel_size];
    int *ptr = new int [pixel_size*3];
    for(int i = 0; i < pixel_size; i++, ptr += 3)
    {
        rgb[i] = ptr;
        rgb[i][0] = 0, rgb[i][1] = 0, rgb[i][2] = 0;
    }
    ComplexSample point;
    int index;
    int point_color[CLASS_N][3] = {
            {255, 0, 0},
            {0, 255, 0},
            {0, 255, 0},
            {0, 255, 0},
            {0, 0, 255}
    };
    for(int i = 0; i < CLASS_N; i++)
    {
        std::cout<<"Class "<<i<<": "<<sampler.get_sampler_count(i)<<std::endl;
        while(sampler.get_sample(i, point))
        {
            point.cam.x *= RESOLUTION, point.cam.y *= RESOLUTION;
            index = ((int)point.cam.y) * RESOLUTION + (int)point.cam.x;
            rgb[index][0] = point_color[i][0];
            rgb[index][1] = point_color[i][1];
            rgb[index][2] = point_color[i][2];
        }
        char file_name[20];
        std::sprintf(file_name, "output%d.png", i);
        write_png_file(RESOLUTION, RESOLUTION, rgb, file_name);
        memset(rgb[0], 0, RESOLUTION*RESOLUTION*3*sizeof(int));
    }
    write_png_file(RESOLUTION, RESOLUTION, rgb, "output.png");

//    if(argv <= 1 || (argv >= 2 && strcmp(argc[1], "--help") == 0)) {
//        std::cout<<"usage:"<<std::endl;
//        std::cout<<"--file OBJ_file --ray [Ox,Oy,Oz] [Dx,Dy,Dz]"<<std::endl;
//        return 0;
//    }
//    else if(strcmp(argc[1], "--file") == 0){
//        std::vector<Polygon> polygons;
//        double parse_start = clock(), parse_end;
//        Transform transform = Translate(Vector3D(1, 1, -1));
//        TriMesh *mesh = create_mesh_from_obj(transform, argc[2]);
//        parse_end = clock();
//        std::cout<<"Cost time: "<<(parse_end - parse_start)/CLOCKS_PER_SEC<<" s\n";
//        delete mesh;
//        parse_end = clock();
//        std::cout<<"Cost time: "<<(parse_end - parse_start)/CLOCKS_PER_SEC<<" s\n";
//        Ray test_ray;
//        if(strcmp(argc[3], "--ray") == 0)
//        {
//            try {
//                std::string o_str(argc[4]);
//                std::string d_str(argc[5]);
//                o_str = o_str.substr(1, o_str.size() - 2);
//                d_str = d_str.substr(1, d_str.size() - 2);
//                unsigned long index1 = o_str.find(','), index2 = o_str.rfind(',');
//                float x, y, z;
//                x = std::stof(o_str.substr(0, index1));
//                y = std::stof(o_str.substr(index1 + 1, index2 - index1 - 1));
//                z = std::stof(o_str.substr(index2 + 1));
//                Point3D origin(x, y, z);
//                index1 = d_str.find(','), index2 = d_str.rfind(',');
//                x = std::stof(d_str.substr(0, index1));
//                y = std::stof(d_str.substr(index1 + 1, index2 - index1 - 1));
//                z = std::stof(d_str.substr(index2 + 1));
//                Vector3D direction(x, y, z);
//                test_ray = Ray(origin, direction);
//            } catch (std::exception &e)
//            {
//                std::cout<<"Error coordinate syntax"<<std::endl;
//            }
//        }
//        IntersectInfo info;
//        float hit_t;
//
//        double start_t = clock(), end_t;
//        for(Polygon polygon : polygons)
//        {
//            if(polygon.intersect(test_ray, hit_t, info))
//            {
//                std::cout<<"Intersect: "<<std::endl;
//                std::vector<Point3D> hit_polygon_points = polygon.get_vertics();
//                std::cout<<"Hit polygon: ";
//                for(Point3D p : hit_polygon_points)
//                    std::cout<<"("<<p.x<<","<<p.y<<","<<p.z<<")  ";
//                std::cout<<std::endl;
//                std::cout<<"Hit point: ("<<info.hit_p.x<<","<<info.hit_p.y<<","<<info.hit_p.z<<")"<<std::endl;
//            }
//        }
//        end_t = clock();
//#ifdef WIN32
//        std::cout<<"Cost time: "<<(end_t - start_t)/CLK_TCK<<" s\n";
//#elif linux
//        std::cout<<"Cost time: "<<(end_t - start_t)/CLOCKS_PER_SEC<<" s\n";
//#endif
//    }

    return 0;
}
