public class Main {
    public static void main(String[] args) {
        Dealership dealership=new Dealership();
        Customer customer1=new Customer("Florin","Cordos");
        Customer customer2=new Customer("John","Travolta");
        GasolineCar car1=new GasolineCar("Wolksvagen","Polo",2007,2300,230000);
        GasolineCar car4=new GasolineCar("Skoda","Octavia",2002,2300,320000);
        DieselCar car2=new DieselCar("Audi","A2",2010,1500,190000);
        DieselCar car3=new DieselCar("BMW","X4",2012,5000,230000);
        dealership.addCar(car1);
        dealership.addCar(car2);
        dealership.addCar(car3);
        dealership.addCar(car4);
       // customer1.buyCar(dealership,car1);
        //adauga car1 de 3 ori
       // dealership.addCar(car1,3);
       // customer1.buyAllCars(dealership);
        customer2.buyCar(dealership,car1);
        dealership.listInventory();
        customer1.showDetails();
        customer2.showDetails();
        //discount for new customer
    }
}