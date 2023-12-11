#include<bits/stdc++.h>

#define maxBackoff 10			//maximum backoff interval
#define numSlots 50				//number of time slots for demonstration
#define maxPacketLength 4		//maximum possible packet length

using namespace std;

//vector to store nodes which done transmitting
vector<int> successfulTransmissions;
int Totalcollisions = 0;

//Channel has channelNodes which are currently using channel
class Channel
{
public:
    set<int> channelNodes = {};

    bool isIdle()
    {
        return channelNodes.size() == 0;
    }

    bool isBusy()
    {
        return !isIdle();
    }
	
	
    void clear()
    {
        channelNodes = {};
    }
};

class Node
{
public:
    int id;						//node identifier
    int dataSendingTime;		//time requried to send data
    int backoff;				//remaining waiting time
    bool transmitting;			//true=>currently transmitting data
    int timesent;				//spent this time sending the data
    int backoffAttempts;		//number of attempts
    int collisions;				//number of collisions it experienced
	

	//constructor
    Node(int id, int dataSendingTime) : id(id), dataSendingTime(dataSendingTime), backoff(0), transmitting(false), timesent(0), backoffAttempts(0), collisions(0) {}
	
	//generate backoff value randomly 
    void Backoff()
    {
        timesent = 0;
        backoff = rand() % maxBackoff + 1;
        cout << "Node " << id << " backed off by " << backoff << endl;
        backoffAttempts++;
    }

    void Collide()
    {
        cout << "Node " << id << " collided with other nodes and ";
        collisions++;
    }

	//if channel has exactly 1 node and that is the same node as this node
	//then we can continue transmmision otherwise not
    bool attemptTransmission(Channel &channel)
    {
        if (channel.channelNodes.size() == 1 and *channel.channelNodes.begin() == id)
        {
            return true;
        }
        if (timesent == dataSendingTime)
        {
            return false;
        }
        if (channel.isBusy())
        {
            Backoff();			//sssssshould be backed off when channel is busy
            return false;
        }
        return true;
    }

	//add this node to channel
    void transmit(Channel &channel)
    {
        channel.channelNodes.insert(id);
        timesent++;
    }
	
	//check whether it is partially done or not
    bool donePartially()
    {
        return timesent < dataSendingTime and timesent > 0;
    }

    void decrementBackoff()
    {
        if (backoff > 0)
        {
            backoff--;
        }
    }
};

int main()
{
    srand(time(0));   //seeding with current time stamp to generate differnet values when it run again

    int numNodes;
    Channel oldchannel, channel;  // oldchannel corresponds to channel in previous time slot
    vector<Node> nodes;

    cout<<"Number of Nodes in network: ";
    cin>>numNodes;

    cout<<"Enter y if you want to manually give data sending time for nodes else enter n to generate them randomly"<<endl;
	
	//taking data sending time from input or generating them randomly 
    char c;
    cin>>c;
    if (c=='y'){
        for (int i = 0; i < numNodes; i++)
        {
            int dataSendingTime;
            cout<<"Enter Data Sending Time for Node "<<i<<": ";
            cin>>dataSendingTime;
            nodes.push_back(Node(i, dataSendingTime));
        }
    }

    else {
        cout<<"Data Sending Times:"<<endl;

        for (int i = 0; i < numNodes; i++)
        {
            int dataSendingTime = (rand() % maxPacketLength) + 1;
            nodes.push_back(Node(i, dataSendingTime));
            cout << "Node "<<i << ": " << dataSendingTime << endl;
        }
    }


	//demonstartion in every time slot
    for (int slot = 0; slot < numSlots; slot++)
    {
        
        cout << "\nTime " << slot + 1 << " :" << endl;


        set<int> oldChannel = oldchannel.channelNodes;

		//remove the nodes from oldchannel which are done transmitting whole data
        for (auto &node : nodes)
        {
            for (auto &id : oldChannel)
            {
                if (id == node.id && !node.donePartially())
                {
                	if (oldchannel.channelNodes.find(id) != oldchannel.channelNodes.end())
                    	oldchannel.channelNodes.erase(oldchannel.channelNodes.find(node.id));
                	successfulTransmissions.push_back(id);
                    
                }
            }
        }
        
        if(successfulTransmissions.size()==numNodes){cout<<"\nAll done transmitting\n";break;}

		//nodes which are in oldchannel and left with some more data to transmit
        cout << "Nodes of Prev transition still continuing :";

        for (auto node : oldchannel.channelNodes)
        {
            cout << node << " ";
        }
        cout << endl;

		//we can transmit data if oldchannel is not busy otherwise need to be backed off
        for (auto &node : nodes)
        {
            if (node.backoff == 0)
            {
                if (node.attemptTransmission(oldchannel))
                    node.transmit(channel);
            }
        }

		//These are the nodes which are now intrested in transmitting data
        cout << "Nodes of current transition : ";

        for (auto &node : channel.channelNodes)
        {
            cout << node << " ";
        }
        cout << endl;

		//if morethan 1 nodes are intrested then collision happens(collision detection) all the nodes need to be 
		//backed off else it can go successfully
        if (channel.channelNodes.size() > 1)
        {
            for (auto &node : nodes)
            {
                for (auto &id : channel.channelNodes)
                {
                    if (id == node.id)
                    {
                        node.Collide();
                        node.Backoff();
                    }
                }
            }
            Totalcollisions++;
            channel.clear();
        }
		//made the channel as oldchannel for new iteration and clear the current channel
        oldchannel = channel;
        channel.clear();
		
		//decrementing backoff value in every iteration
        for (auto &node : nodes)
        {
            node.decrementBackoff();        
        }
        

    }

	
	//report from above demonstration
	cout<<"Number of nodes which Successfully Transmitted entire message: "<<successfulTransmissions.size()<<endl;

    cout << "And the nodes are:  ";
    sort(successfulTransmissions.begin(),successfulTransmissions.end());
    for (auto &x: successfulTransmissions){
        cout<<x<<" ";
    }
    if (successfulTransmissions.size()==0){cout<<"None";}
    cout<<endl;
    
    cout << "Total Number of Collisions: " << Totalcollisions << endl;
    cout << "Backoff Attempts: " << endl;
    int sum=0;
    for (auto &node:nodes){
        cout<<"Node "<<node.id<<": "<<node.backoffAttempts<<endl;
        sum+=node.backoffAttempts;
    }
    cout<<"Total Number of Backoff Attempts: "<<sum<<endl<<endl;

    return 0;
}
